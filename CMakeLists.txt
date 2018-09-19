# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_BUILD_TYPE Release) 

#Linux
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
#Windows
#set(CMAKE_CXX_FLAGS_RELEASE "-Ox")

set(BUILD_STATIC_LIBS ON)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

link_directories (${PROJECT_BINARY_DIR})
include_directories(lib)
include_directories(lib/Probability)
include_directories(lib/Base64)
include_directories(lib/Rapidjson)


add_library(mainLibrary 
                    lib/RapidjsonUtils.cpp
                    lib/General.cpp
#					lib/GeneralWindows.cpp
					lib/GeneralLinux.cpp
                    lib/Card.cpp
                    lib/FunctionsToRate.cpp
                    lib/Probability/Probability.hpp
					lib/Base64/Base64.cpp
                    lib/Hearthstone.cpp
                    lib/HearthstoneDeck.cpp
					lib/HSReplay.cpp
                    lib/CollectOBot.cpp
                    )

project ("DeckFinder")

# Include sub-projects.
add_subdirectory ("DeckFinder")
add_subdirectory ("PrepareCards")
add_subdirectory ("MatchCollector")
add_subdirectory ("RecursiveFiller")
add_subdirectory ("DeckRater")
add_subdirectory ("Playground")
