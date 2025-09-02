// Read files and prints top k word by frequency

#include <algorithm>
#include <atomic>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <future>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <mutex>
#include <numeric>
#include <queue>
#include <stdexcept>
#include <string>
#include <sstream>
#include <thread>
#include <vector>


#if defined(USE_SHARED_DICT) && defined(USE_LOCAL_DICTS)
#error "Cannot define both USE_SHARED_DICT and USE_LOCAL_DICTS at the same time"
#endif

#if !defined(USE_SHARED_DICT) && !defined(USE_LOCAL_DICTS)
#define USE_LOCAL_DICTS  // Default to local dictionaries if neither is defined
#endif


const size_t TOPK = 10;
using Counter = std::map<std::string, std::size_t>;
std::string tolower(const std::string &str);
void count_words(std::istream& stream, Counter&);
void print_topk(std::ostream& stream, const Counter&, const size_t k);
unsigned int benchmark_optimal_threads(const unsigned int threadsAmount = std::thread::hardware_concurrency());


/* 
    Choose between the hardware threads amount and the provided threads that the caller wants us to test
    as the maximum amount of threads to use.
*/
unsigned int benchmark_optimal_threads(const unsigned int threadsAmount)
{
    const unsigned int threadsMax = std::min(threadsAmount, std::thread::hardware_concurrency());
    const unsigned int threadsMin = 1;
    const unsigned int step = 1;
    const unsigned int iterationsAmount = 111;  // Number of benchmark iterations
    const unsigned int wordsTotal = 3333;   // Total words to process (fixed amount)
    const unsigned int filesTotal = 32;         // Number of files to process (fixed amount)

    std::vector<unsigned int> threads;
    for(unsigned int i = threadsMin; i <= threadsMax; i += step)
    {
        threads.push_back(i);
    }

    std::vector<double> times(threads.size());

    /*
        Create a FIXED set of test files
    */
    std::vector<std::string> test_files;    
    for(unsigned int i = 0; i < filesTotal; ++i)
    {
        std::string file_content;
        /* 
            Each file gets an equal portion of the total words 
            (we know that the total amount of words is fixed)
        */
        for(unsigned int j = 0; j < wordsTotal / filesTotal; ++j)
        {
            file_content += "word_" + std::to_string(i) + "_" + std::to_string(j) + " ";
            /*
                Add some variety to word frequencies
            */
            if(j % 10 == 0)
            {
                file_content += "common_word ";
            }
            if(j % 100 == 0)
            {
                file_content += "very_common_word ";
            }
        }
        test_files.push_back(file_content);
    }

    for(size_t i = 0; i < threads.size(); ++i)
    {
        unsigned int num_threads = threads[i];
        std::vector<std::future<void>> futures;

        auto start = std::chrono::high_resolution_clock::now();

        /*
            Calculate how many files each thread should process
        */
        unsigned int files_per_thread = (filesTotal + num_threads - 1) / num_threads; // Ceiling division

        /*
            Launch threads to process the files
        */
        for(unsigned int thread_idx = 0; thread_idx < num_threads; ++thread_idx)
        {
            futures.push_back(std::async(std::launch::async, 
                [&test_files, thread_idx, num_threads, files_per_thread, iterationsAmount, filesTotal]() {
                    Counter local_counter;
                    /*
                        Each thread processes its portion of files
                    */
                    for(unsigned int file_idx = 0; file_idx < files_per_thread; ++file_idx)
                    {
                        size_t file_num = thread_idx * files_per_thread + file_idx;
                        if(file_num >= filesTotal) 
                        {
                            break; // Don't process more files than we have
                        }
                        
                        /*
                            Simulate file reading and processing
                        */
                        for(unsigned int iter = 0; iter < iterationsAmount; ++iter)
                        {
                            std::istringstream stream(test_files[file_num]);
                            /*
                                Simulate some I/O delay
                            */
                            std::this_thread::sleep_for(std::chrono::microseconds(10));
                            count_words(stream, local_counter);
                        }
                    }
                }));
        }

        for(auto& fut : futures)
        {
            fut.get();
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        times[i] = duration.count();
        std::cout << "  " << num_threads << " threads: " << times[i] << " ms" << std::endl;
    }

    auto minTimeIt = std::min_element(times.begin(), times.end());
    size_t minTimeIndex = static_cast<size_t>(std::distance(times.begin(), minTimeIt));
    return threads[minTimeIndex];
}

void merge_counters(Counter& main_dict, const Counter& local_dict)
{
    for(const auto& pair : local_dict)
    {
        main_dict[pair.first] += pair.second;
    }
}


Counter process_file_task(const std::string& filepath)
{
    Counter local_counter;
    
    std::ifstream input{filepath};
    if(input.is_open() == false)
    {
        throw std::runtime_error("Failed to open file: " + filepath);
    }
    count_words(input, local_counter);
    
    return local_counter;
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto mainStart = std::chrono::high_resolution_clock::now();
    Counter freqDictFinal;

#if defined(USE_MULTI_THREADING) && USE_MULTI_THREADING == 1
    std::cout << "Using multi-threading." << std::endl;
    std::vector<std::string> files_to_process;
    for(int i = 1; i < argc; ++i)
    {
        files_to_process.push_back(argv[i]);
    }

    std::cout<<"Start simple benchmark test..."<<std::endl;
    unsigned int threadsAmountOptimal = benchmark_optimal_threads(static_cast<unsigned int>(files_to_process.size()));
    std::cout << "Optimal thread count: " << threadsAmountOptimal << std::endl;

    std::queue<std::string> file_queue;
    for(const std::string& filepath : files_to_process)
    {
        file_queue.push(filepath);
    }

    std::atomic<unsigned int> tasksInProgress{0};

    mainStart = std::chrono::high_resolution_clock::now();
#if defined(USE_SHARED_DICT) && USE_SHARED_DICT == 1
    std::mutex dict_mutex;
    std::cout << "Using the shared dictionary protected by mutex" << std::endl;
    std::vector<std::future<void>> futures;  // For shared dict, futures return void
#else
    std::cout << "Using local dictionaries with final merge." << std::endl;
    std::vector<std::future<Counter>> futures;  // For local dicts, futures return Counter
#endif

    while(file_queue.empty() == false || tasksInProgress > 0)
    {
        // Launch new tasks if possible
        while(tasksInProgress < threadsAmountOptimal && file_queue.empty() == false)
        {
            std::string filepath = file_queue.front();
            file_queue.pop();
            ++tasksInProgress;

#if defined(USE_SHARED_DICT) && USE_SHARED_DICT == 1
            futures.push_back(std::async(std::launch::async, 
                [filepath, &tasksInProgress, &freqDictFinal, &dict_mutex]() 
                {
                    try 
                    {
                        std::ifstream input{filepath};
                        if(input.is_open() == false)
                        {
                            std::cerr << "Failed to open file " << filepath << '\n';
                            --tasksInProgress;
                            return;
                        }
                        
                        // Create temporary counter for this file
                        Counter local_counter;
                        count_words(input, local_counter);
                        
                        // Merge into shared dictionary with mutex protection
                        {
                            std::lock_guard<std::mutex> lock(dict_mutex);
                            merge_counters(freqDictFinal, local_counter);
                        }
                    } 
                    catch(const std::exception& e)
                    {
                        std::cerr << "Error processing file in a thread: " << e.what() << std::endl;
                    }
                    --tasksInProgress;
                }));
#else
            futures.push_back(std::async(std::launch::async, 
                [filepath, &tasksInProgress]() 
                {
                    Counter local_counter;
                    try 
                    {
                        std::ifstream input{filepath};
                        if(input.is_open() == false)
                        {
                            std::cerr << "Failed to open file " << filepath << '\n';
                            --tasksInProgress;
                            return local_counter;
                        }
                        count_words(input, local_counter);
                    } 
                    catch(const std::exception& e)
                    {
                        std::cerr << "Error processing file in a thread: " << e.what() << std::endl;
                    }
                    --tasksInProgress;
                    return local_counter;
                }));
#endif
        }

        // Check for completed tasks and remove them from the futures vector
        auto it = futures.begin();
        while(it != futures.end())
        {
            if(it->wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
            {
#if !defined(USE_SHARED_DICT) || USE_SHARED_DICT != 1
                try
                {
                    Counter counterLocal = it->get();
                    merge_counters(freqDictFinal, counterLocal);
                }
                catch(const std::exception& e)
                {
                    std::cerr << "Error getting future result: " << e.what() << std::endl;
                }
#else
                try
                {
                    it->get();  // Just wait for completion, no return value to process
                } 
                catch(const std::exception& e)
                {
                    std::cerr << "Error in shared dictionary task: " << e.what() << std::endl;
                }
#endif
                it = futures.erase(it);
            } 
            else
            {
                ++it;
            }
        }

        // Small sleep to prevent busy waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

#else
    std::cout << "Using single-threading." << std::endl;
    mainStart = std::chrono::high_resolution_clock::now();
    for(int i = 1; i < argc; ++i)
    {
        std::ifstream input{argv[i]};
        if(input.is_open() == false)
        {
            std::cerr << "Failed to open file " << argv[i] << '\n';
            continue;
        }
        count_words(input, freqDictFinal);
    }
#endif

    print_topk(std::cout, freqDictFinal, TOPK);
    auto timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - mainStart);
    std::cout << "Elapsed time is " << timeElapsed.count() << " us\n";
    return EXIT_SUCCESS;
}

std::string tolower(const std::string &str)
{
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void count_words(std::istream& stream, Counter& counter)
{
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(), // end of stream (default ctor)
                  [&counter](const std::string &s) { ++counter[tolower(s)]; });    
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k)
{
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for(auto it = std::cbegin(counter); it != std::cend(counter); ++it)
    {
        words.push_back(it);
    }

    auto num_elements_to_sort = static_cast<std::ptrdiff_t>(std::min(k, words.size()));

    std::partial_sort(
        std::begin(words), std::begin(words) + num_elements_to_sort, std::end(words),
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(std::begin(words), std::begin(words) + num_elements_to_sort,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                      << '\n';
        });
}

