cmake_minimum_required(VERSION 3.9)
project(boggle_ml)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-release/)

set(SOURCE_FILES
    board_evaluator.hpp
    board_evaluator.cpp
    common.hpp
    prefix_trie.hpp
    prefix_trie.cpp)

set(TEST_SOURCE_FILES
    tests/test_prefix_trie.cpp
    tests/test_board_evaluator.cpp)



if(UNIX)
	add_executable(boggle_ml main.cpp ${SOURCE_FILES})
	add_executable(test_boggle_ml tests/test_main.cpp ${SOURCE_FILES} ${TEST_SOURCE_FILES})

	include_directories("/usr/include")

endif(UNIX)


if(WIN32)
	add_executable(boggle_ml main.cpp ${SOURCE_FILES})
	add_executable(test_boggle_ml tests/test_main.cpp ${SOURCE_FILES} ${TEST_SOURCE_FILES})

	include_directories("C:\\Program Files (x86)\\Microsoft Visual Studio\\Shared\\include")
	link_directories("C:\\Program Files (x86)\\Microsoft Visual Studio\\Shared\\lib")
endif(WIN32)