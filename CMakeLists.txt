cmake_minimum_required(VERSION 3.20)

project(guess_the_number
		VERSION 0.7
		LANGUAGES CXX
		DESCRIPTION "Simple game generating a random number for user to guess it"
)

set(CMAKE_CXX_COMPILER	"/usr/bin/g++")
set(CURDIR ${CMAKE_SOURCE_DIR})
set(ARTI_ELF ${PROJECT_NAME})

set(INCLUDE_DIRECTORIES 
	${CURDIR}
)

set(CPP_COMPILE_DEFINITIONS 
	# -DGUESS_RECORDS_FILE="${CURDIR}/stat/guess_high_scores_duplicates.txt"
	-DGUESS_RECORDS_FILE="${CURDIR}/stat/guess_high_scores.txt"
	-DGUESS_MAX_LEVEL_1=10
	-DGUESS_MAX_LEVEL_2=50
	-DGUESS_MAX_LEVEL_3=100
)

set(CPP_OPTIONS_WIN
	"/W4"
	"/WX"
)

set(CPP_OPTIONS_NIX
	"-Wall"
	"-Wextra"
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(${CPP_OPTIONS_NIX} 
        "-g3"
		"O0"
	)
else()
	set(${CPP_OPTIONS_NIX} 
		"Os"
	)
endif()


set(CPP_SOURCES
	${CURDIR}/src/guess_the_number.cpp
)

add_executable(${ARTI_ELF} ${CPP_SOURCES})

target_compile_definitions(${ARTI_ELF} PRIVATE
	${CPP_COMPILE_DEFINITIONS}
)

target_compile_features(${ARTI_ELF} PRIVATE cxx_std_17)
set_target_properties(${ARTI_ELF} PROPERTIES CXX_STANDARD_REQUIRED ON)

if(MSVC)
        target_compile_options(${ARTI_ELF} PRIVATE 
			${CPP_OPTIONS_WIN}
		)
		target_link_options(${ARTI_ELF} PRIVATE
			${CPP_OPTIONS_WIN}
		)
else()
        target_compile_options(${ARTI_ELF} PRIVATE
			${CPP_OPTIONS_NIX}
		)
		target_link_options(${ARTI_ELF} PRIVATE
			${CPP_OPTIONS_NIX}
		)
endif()

