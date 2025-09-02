#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <endian.h>
#include <future>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <thread>
#include <vector>

#include "inc/CRC32.hpp"
#include "inc/IO.hpp"

// Conditional includes for multi-threading
#if defined(USE_MULTI_THREADING) && USE_MULTI_THREADING == 1
/**
 * @brief Searches a specific range of 4-byte values for one that results in the target CRC.
 *        (Worker function for multi-threaded version)
 *
 * @param startValue The starting value of the range (inclusive).
 * @param endValue The ending value of the range (exclusive).
 * @param targetCrc32 The desired final CRC32 value.
 * @param precomputedCrc The intermediate CRC32 value calculated up to the point before the 4 bytes.
 * @param found Reference to atomic flag for cooperative cancellation.
 * @return An optional containing the matching 4-byte value if found, otherwise std::nullopt.
 */
std::optional<uint32_t> pickMatchingCrc(uint64_t startValue, uint64_t endValue,
                                          uint32_t targetCrc32, uint32_t precomputedCrc,
                                          std::atomic<bool>& found)
{
    constexpr uint64_t CHECK_INTERVAL = 10000;
    for(uint64_t iLong = startValue, check = 0; iLong < endValue; ++iLong, ++check)
    {
        if (check % CHECK_INTERVAL == 0 && found.load(std::memory_order_relaxed))
            return std::nullopt;
        uint32_t i = static_cast<uint32_t>(iLong);
        auto currentCrc32 = crc32Final(reinterpret_cast<const char*>(&i), sizeof(i), precomputedCrc);
        if(currentCrc32 == targetCrc32)
        {
            found.store(true, std::memory_order_relaxed);
            return i; // Found it!
        }
    }
    return std::nullopt; // Not found in this range
}
#endif // USE_MULTI_THREADING

/// @brief Переписывает последние 4 байта значением value
void replaceLastFourBytes(std::vector<char> &data, uint32_t value)
{
  std::copy_n(reinterpret_cast<const char *>(&value), 4, data.end() - 4);
}

/**
 * @brief Формирует новый вектор с тем же CRC32, добавляя в конец оригинального
 * строку injection и дополнительные 4 байта
 * @details При формировании нового вектора последние 4 байта не несут полезной
 * нагрузки и подбираются таким образом, чтобы CRC32 нового и оригинального
 * вектора совпадали
 * @param original оригинальный вектор
 * @param injection произвольная строка, которая будет добавлена после данных
 * оригинального вектора
 * @return новый вектор
 */
std::vector<char> hack(const std::vector<char> &original,
                        const std::string &injection)
{
    const uint32_t originalCrc32 = crc32Final(original.data(), original.size());
    std::cout << "Injection: " << injection << std::endl;
    std::cout << "Original CRC32: 0x" << std::setw(8) << std::setfill('0') << std::hex << htobe32(originalCrc32) << std::dec << std::endl;

    std::vector<char> result(original.size() + injection.size() + 4);
    auto it = std::copy(original.begin(), original.end(), result.begin());
    std::copy(injection.begin(), injection.end(), it);
    const uint32_t currentCrc32Precompute = crc32Intermediate(result.data(), original.size() + injection.size());

#if defined(USE_MULTI_THREADING) && USE_MULTI_THREADING == 1
    std::atomic<bool> found{false};
    /* 
      --- Benchmarking Phase --- 
      For dynamic balancing of threads
      Aim is to find optimal number of threads to solve the task
    */
    std::cout << "Benchmarking thread performance..." << std::endl;
    const std::vector<unsigned int> threadAmount = {1, 2, 4, 8, 10, 12, 14, 16, 32};
    std::map<unsigned int, double> durations;
    const uint64_t benchmark_range_size = 10'000'000; // Benchmark first 10M values
    const uint64_t rangeSizeTotal = static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) + 1;

    for(unsigned int threadNumber : threadAmount)
    {
      static unsigned int concurrency = std::thread::hardware_concurrency();
      if(threadNumber > concurrency && concurrency > 0)
      {
        std::cout << "Skipping benchmark for " << threadNumber << " threads (more than hardware concurrency: " << concurrency << ")" << std::endl;
        continue;
      }
      if(benchmark_range_size < threadNumber)
      {
        std::cout << "Skipping benchmark for " << threadNumber << " threads (benchmark size too small)" << std::endl;
        continue;
      }

      std::vector<std::future<std::optional<uint32_t>>> futures;
      uint64_t valuesPerThread = benchmark_range_size / threadNumber; // Use benchmark size here
      uint64_t valueStart = 0;

      auto timeStart = std::chrono::high_resolution_clock::now();

      for(unsigned int i = 0; i < threadNumber; ++i)
      {
        uint64_t valueEnd = valueStart + valuesPerThread;
        if(i == threadNumber - 1)
        {
          valueEnd = benchmark_range_size; // End at benchmark size
        }
        futures.push_back(std::async(std::launch::async, pickMatchingCrc,
                                    valueStart, valueEnd,
                                    originalCrc32, currentCrc32Precompute,
                                    std::ref(found)));
        valueStart = valueEnd;
      }

      for(auto& fut : futures)
      {
        fut.get(); // We don't care about the result in the benchmark phase
      }

      auto timeEnd = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> duration = timeEnd - timeStart;
      durations[threadNumber] = duration.count();
      std::cout << "  " << threadNumber << " threads: " << durations[threadNumber] << " ms" << std::endl;
    }

    unsigned int threadsAmountOptimal = 1;
    double minTime = std::numeric_limits<double>::max();
    if(durations.empty() == false)
    {
      auto entryBest = std::min_element(durations.begin(), durations.end(),
                                           [](const auto& a, const auto& b)
                                           {
                                               return a.second < b.second;
                                            });
      threadsAmountOptimal = entryBest->first;
      minTime = entryBest->second;
    } 
    else
    {
      threadsAmountOptimal = 1;
      minTime = 0; // Indicate no benchmark was run
    }

    std::cout << "Optimal thread count: " << threadsAmountOptimal << " (Benchmark time: " << minTime << " ms)" << std::endl;
    std::cout << "Starting full search..." << std::endl;

    // Reset the flag before the full search
    found.store(false, std::memory_order_relaxed);
    std::vector<std::future<std::optional<uint32_t>>> futuresPick;
    uint64_t valuesPerThreadFull = rangeSizeTotal / threadsAmountOptimal;
    uint64_t valueStartFull = 0;

    auto timeStartSearch = std::chrono::high_resolution_clock::now();

    for(unsigned int i = 0; i < threadsAmountOptimal; ++i)
    {
      uint64_t valueEndFull = valueStartFull + valuesPerThreadFull;
      if(i == threadsAmountOptimal - 1)
      {
        valueEndFull = rangeSizeTotal; 
      }
      futuresPick.push_back(std::async(std::launch::async, pickMatchingCrc,
                                         valueStartFull, valueEndFull,
                                         originalCrc32, currentCrc32Precompute,
                                         std::ref(found)));
      valueStartFull = valueEndFull;
    }

    std::optional<uint32_t> foundValue = std::nullopt;
    for(auto& fut : futuresPick)
    {
      std::optional<uint32_t> threadResult = fut.get();
      if(threadResult.has_value())
      {
        foundValue = threadResult;
        break; 
      }
    }

    auto timeEndSearch = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationSearch = timeEndSearch - timeStartSearch;
    std::cout << "Full search completed in: " << durationSearch.count() << " s" << std::endl;

    if(foundValue.has_value())
    {
      uint32_t i = foundValue.value();
      replaceLastFourBytes(result, i);
      std::cout << "Bytes to add: 0x" << std::setw(8) << std::setfill('0') << std::hex << htobe32(i) << std::dec << std::endl;
      return result;
    } 
    else
    {
      throw std::logic_error("Can't hack: No matching CRC found in the entire range.");
    }

#else // USE_MULTI_THREADING defined

    /*
        --- Single-threaded implementation --- 
    */
    std::cout << "Using single-threaded implementation." << std::endl;
    const uint64_t total_range_size = static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) + 1;
    auto timeStartSearch = std::chrono::high_resolution_clock::now();

    for(uint64_t i_long = 0; i_long < total_range_size; ++i_long) 
    {
        uint32_t i = static_cast<uint32_t>(i_long);
        auto currentCrc32 = crc32Final(reinterpret_cast<const char*>(&i), sizeof(i), currentCrc32Precompute);
        if(currentCrc32 == originalCrc32)
        {
            replaceLastFourBytes(result, i);
            std::cout << "Bytes to add: 0x" << std::setw(8) << std::setfill('0') << std::hex << htobe32(i) << std::dec << std::endl;

            auto timeEndSearch = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationSearch = timeEndSearch - timeStartSearch;
            std::cout << "Search completed in: " << durationSearch.count() << " s" << std::endl;

            return result;
        }
    }
    
    // This should not be reached if a solution always exists
    throw std::logic_error("Can't hack: No matching CRC found in the entire range (single-threaded).");

#endif // USE_MULTI_THREADING
}

int main(int argc, char **argv)
{
  if(argc != 3)
  {
    std::cerr << "Call with two args: " << argv[0]
              << " <input file> <output file>\n";
    return 1;
  }

  try
  {
    const std::vector<char> data = readFromFile(argv[1]);
    const std::vector<char> badData = hack(data, "He-he-he");
    writeToFile(argv[2], badData);
  } 
  catch(std::exception &ex)
  {
    std::cerr << ex.what() << '\n';
    return 2;
  }
  std::cout << "Status: Success\n";
  return 0;
}

