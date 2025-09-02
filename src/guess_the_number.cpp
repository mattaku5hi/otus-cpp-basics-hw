#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <getopt.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>


#ifndef GUESS_RECORDS_FILE
#define GUESS_RECORDS_FILE	"../stat/guess_high_scores.txt"
#endif

#ifndef GUESS_MAX_LEVEL_1
#define GUESS_MAX_LEVEL_1		10
#endif

#ifndef GUESS_MAX_LEVEL_2
#define GUESS_MAX_LEVEL_2		50
#endif

#ifndef GUESS_MAX_LEVEL_3
#define GUESS_MAX_LEVEL_3		100
#endif


class GuessNumber
{
	public:
		GuessNumber(const std::string& fileScoresPath);
        ~GuessNumber();
        /* Prevent instance copy and copy with assignment */
        GuessNumber(const GuessNumber&) = delete;
        GuessNumber& operator=(const GuessNumber&) = delete;

        enum class guessStatusCode;
        struct guessStatusTuple;
		struct guessParams;

		guessStatusTuple guessProcess(int argc, char** argv);

		enum class guessStatusCode
		{
			GUESS_OK,

			GUESS_INCORRECT_ARGS,
			GUESS_INCORRECT_USERNAME,
			GUESS_ERROR_FILE_OPEN,
		};

		struct guessStatusTuple
		{
			guessStatusCode code;
			std::string desc;
		};

		struct guessParams
		{
			unsigned int max{0};
			bool isTableMode = false;
			std::uint8_t level{0};
		};


	private:
		std::string m_file_scores;

		inline void guessLevel2Max(guessParams& params);
		guessStatusTuple guessOptionCheck(int argc, char** ppArgv, guessParams& params);
		guessStatusTuple guessUserAuthorize(std::string& userName);
		guessStatusTuple guessResultPrint(const std::string& fileName);
		guessStatusTuple guessResultStore(const std::string& fileName, const std::string& userName, const unsigned int attempts);
		inline int guessRandomGenerate(const int limitMax);
		guessStatusTuple guessLoop(const int valueTarget, unsigned int& attempts);
};


GuessNumber::GuessNumber(const std::string& fileScoresPath) :
    m_file_scores(fileScoresPath)
{
    if(m_file_scores.empty())
    {
        throw std::runtime_error("Failed to acquire resource: empty string");
    }

} 

/**
 * @brief 
 */
GuessNumber::~GuessNumber()
{
}


inline void GuessNumber::guessLevel2Max(guessParams& params)
{
	if(params.level == 1)
	{
		params.max = GUESS_MAX_LEVEL_1;
	}
	else if(params.level == 2)
	{
		params.max = GUESS_MAX_LEVEL_2;
	}
	else if(params.level == 3)
	{
		params.max = GUESS_MAX_LEVEL_3;
	}
}

GuessNumber::guessStatusTuple GuessNumber::guessOptionCheck(int argc, char** ppArgv, guessParams& params)
{
	/* argc - it is a count of arguments
	 * But there is some detail - OS always pass one system argument - the name of the executable
	 * So, is the application was executed without arguments at all, argc will be still == 1
	*/

	guessStatusTuple status{.code = guessStatusCode::GUESS_OK, "OK"};
	struct option long_options[] = 
	{
        {"max",   required_argument, 0, 'm'},
        {"table", no_argument,       0, 't'},
        {"level", required_argument, 0, 'l'},
        {0, 0, 0, 0}
    };

	/* Don't forget that the first argument is current utility name! */
    int option_index = 0;
    int c;

    while((c = getopt_long(argc, ppArgv, "m:tl:", long_options, &option_index)) != -1)
	{
        switch(c)
		{
            case 'm':
			{
                if(params.level != 0)
				{
					status.code = guessStatusCode::GUESS_INCORRECT_ARGS;
                    status.desc = "-max and -level options are mutually exclusive";
                    return status;
                }

                char* end;
                unsigned int temp = std::strtoul(optarg, &end, 10);
                if(*end != '\0' || temp <= 1 || temp == std::numeric_limits<unsigned long>::max())
				{
                    status.code = guessStatusCode::GUESS_INCORRECT_ARGS;
                    status.desc = "Invalid -max option value";
                    return status;
                }
				else
				{
					params.max = temp;
				}
                break;
			}
            case 't':
			{
                params.isTableMode = true;
                break;
			}
			case 'l':
			{
                if(params.max != 0)
				{
                    status.code = guessStatusCode::GUESS_INCORRECT_ARGS;
                    status.desc = "-max and -level options are mutually exclusive";
                    return status;
                }

                int temp = std::atoi(optarg);
                if(temp < 1 || temp > 3)
				{
                    status.code = guessStatusCode::GUESS_INCORRECT_ARGS;
                    status.desc = "levels ['1' '2' '3'] are supported";
                    return status;
                }
				else
				{
					params.level = static_cast<unsigned int>(temp);
					this->guessLevel2Max(params);
				}
                break;
			}
            case '?':
            default:
				status.code = guessStatusCode::GUESS_INCORRECT_ARGS;
				status.desc = "Unsuppported option has been specified";
				return status;
        }
    }

	return status;
}

GuessNumber::guessStatusTuple GuessNumber::guessUserAuthorize(std::string& userName)
{
	guessStatusTuple status{.code = guessStatusCode::GUESS_OK, .desc = "OK"};

	// Ask about name
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::cin >> userName;
	if(userName.length() < 2)
	{
		status = {.code = guessStatusCode::GUESS_INCORRECT_USERNAME, .desc = "Incorrect name has been specified"};
		return status;
	}

	return status;
}

GuessNumber::guessStatusTuple GuessNumber::guessResultPrint(const std::string& fileName)
{
	guessStatusTuple status{.code = guessStatusCode::GUESS_OK, .desc = "OK"};
	std::unordered_map<std::string, unsigned int> bestScores;
	std::vector<std::string> bestScoresOrdered;
	
	// Read the high score file and print all results
	std::ifstream fileIn{fileName};
	if(fileIn.is_open() == false) 
	{
		status.code = guessStatusCode::GUESS_ERROR_FILE_OPEN;
		status.desc = "File - " + fileName + " - doesn't exist or can't be opened for reading";
		return status;
	}

	while(true)
	{
		std::string userName;
		unsigned int score = 0;

		// Read the username first
		fileIn >> userName;
		// Read the high score next
		fileIn >> score;

		if(fileIn.fail())
		{
			break;
		}
		// Ignore the end of line symbol
		fileIn.ignore();

		if(bestScores.find(userName) == bestScores.end())
		{
			bestScores[userName] = score;
			bestScoresOrdered.push_back(userName);
		}
		else if(score < bestScores[userName])
		{
			bestScores[userName] = score;
		}
	}

	std::cout << "High scores table (best results):\n";
	/* Print to stdout */
	for(const auto& userName : bestScoresOrdered)
	{
		std::cout << userName << '\t' << bestScores[userName] << '\n';
	}

	return status;
}

GuessNumber::guessStatusTuple GuessNumber::guessResultStore(const std::string& fileName, const std::string& userName, 
																const unsigned int attempts)
{
	bool isUserFound{false};
	bool isShouldUpdate{false};
	guessStatusTuple status{.code = guessStatusCode::GUESS_OK, .desc = "OK"};
    std::filesystem::path originalFile = fileName;
    std::filesystem::path tempFile = originalFile.parent_path() / (originalFile.filename().string() + ".tmp");
    std::ifstream fileIn{fileName};
    std::ofstream fileOut{tempFile};

    if(fileOut.is_open() == false)
    {
        status.code = guessStatusCode::GUESS_ERROR_FILE_OPEN;
        status.desc = "Temporary file can't be opened for writing";
        return status;
    }

	if(fileIn.is_open() == false)
    {
        status.code = guessStatusCode::GUESS_ERROR_FILE_OPEN;
        status.desc = "Temporary file can't be opened for reading";
        return status;
    }

	std::string line;
	while(std::getline(fileIn, line))
	{
		std::istringstream iss(line);
		std::string existingUser;
		unsigned int existingAttempts;
		
		if(iss >> existingUser >> existingAttempts)
		{
			if(existingUser == userName)
			{
				isUserFound = true;
				if(attempts < existingAttempts)
				{
					isShouldUpdate = true;
					fileOut << userName << ' ' << attempts << std::endl;
				}
				else
				{
					fileOut << line << std::endl;
				}
			}
			else
			{
				fileOut << line << std::endl;
			}
		}
		else
		{
			/* Unexpected file format => just copy it */
			fileOut << line << std::endl;
		}
	}
	fileIn.close();

    /* Current user plays at the first time => append his results to file */
    if(!isUserFound)
    {
        fileOut << userName << ' ' << attempts << std::endl;
        isShouldUpdate = true;
    }

    fileOut.close();

    if(isShouldUpdate)
    {
        try
        {
            std::filesystem::rename(tempFile, originalFile);
        }
        catch(const std::filesystem::filesystem_error& e)
        {
            status.code = guessStatusCode::GUESS_ERROR_FILE_OPEN;
            status.desc = "Updating the high score file due to: " + std::string(e.what());
            return status;
        }
    }
    else
    {
        std::filesystem::remove(tempFile);
    }

	return status;
}

inline int GuessNumber::guessRandomGenerate(const int limitMax)
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	const int randomNumber = std::rand() % limitMax;

	return randomNumber;
}

GuessNumber::guessStatusTuple GuessNumber::guessLoop(const int valueTarget, unsigned int& attempts)
{
	int valueAccepted{0};
	guessStatusTuple status{.code = guessStatusCode::GUESS_OK, .desc = "OK"};

	std::cout << "Enter your number:" << std::endl;

	do 
	{
		std::cin >> valueAccepted;
		attempts++;

		if(valueAccepted < valueTarget)
		{
			std::cout << "greater than " << valueAccepted << std::endl;
		}
		else if(valueAccepted > valueTarget)
		{
			std::cout << "less than " << valueAccepted << std::endl;
		}
		else 
		{
			std::cout << "you're right!" << std::endl;
			break;
		}

	} while(true);

	return status;
}

GuessNumber::guessStatusTuple GuessNumber::guessProcess(int argc, char** argv)
{
	guessStatusTuple status{.code = guessStatusCode::GUESS_OK, .desc = "OK"};
	int randomNumber;
	unsigned int attempts{0};
	std::string userName;
	std::string fileHighScore{m_file_scores};
	/* If no options have been specified, launch the game in a middle mode */
	guessParams params{.max = GUESS_MAX_LEVEL_2, .isTableMode = false};
	
	/* Check the accepted arguments */
	status = guessOptionCheck(argc, argv, params);
	if(status.code != guessStatusCode::GUESS_OK)
	{
		return status;
	}
	
	if(params.isTableMode == false)
	{
		/* Identify current user */
		status = guessUserAuthorize(userName);
		if(status.code != guessStatusCode::GUESS_OK)
		{
			return status;
		}

		/* Generate random number in a pre-set range */
		randomNumber = guessRandomGenerate(params.max);

		/* Enter the target loop */
		status = guessLoop(randomNumber, attempts);
		if(status.code != guessStatusCode::GUESS_OK)
		{
			return status;
		}

		status = guessResultStore(fileHighScore, userName, attempts);
		if(status.code != guessStatusCode::GUESS_OK)
		{
			return status;
		}	
	}

	status = guessResultPrint(fileHighScore);
	if(status.code != guessStatusCode::GUESS_OK)
	{
		return status;
	}

	return status;
}


int main(int argc, char** argv)
{
	GuessNumber::guessStatusTuple status;
	std::string fileScores{GUESS_RECORDS_FILE};

	GuessNumber guessInstance(fileScores); // ctor
	status = guessInstance.guessProcess(argc, argv); // main process
	if(status.code != GuessNumber::guessStatusCode::GUESS_OK)
	{
		std::cerr << "Error: " << status.desc << '\n';
	}

	return status.code == GuessNumber::guessStatusCode::GUESS_OK ? EXIT_SUCCESS : EXIT_FAILURE;
}