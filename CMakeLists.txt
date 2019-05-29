# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_BUILD_TYPE Release) 

if(UNIX) 
    message(STATUS ">>> Linux")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif(WIN32)
    message(STATUS ">>> Windows")
    set(CMAKE_CXX_FLAGS_RELEASE "-Ox")
endif()

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
include_directories(lib/Nlohmann)
include_directories(lib/Pugixml)

add_library(mainLibrary 
                    lib/RapidjsonUtils.cpp
                    lib/General.cpp
                    lib/Card.cpp
                    lib/FunctionsToRate.cpp
                    lib/Probability/Probability.hpp
					lib/Base64/Base64.cpp
                    lib/Hearthstone.cpp
                    lib/HearthstoneDeck.cpp
					lib/HSReplay.cpp
                    lib/CollectOBot.cpp
                    lib/Nlohmann/json.hpp
                    lib/NlohmannjsonUtils.cpp
					lib/MyCollectionParser.cpp
                    )

if(UNIX)
    add_library(linuxLibrary lib/GeneralLinux.cpp)
elseif(WIN32)
    add_library(winLibrary lib/GeneralWindows.cpp)
endif()
                    
project ("DeckFinder")

add_executable (DeckFinder "DeckFinder.cpp")
add_executable (PrepareCards "PrepareCards.cpp")
add_executable (MatchCollector "MatchCollector.cpp")
add_executable (DeckRater "DeckRater.cpp")
if(UNIX)
    target_link_libraries(DeckFinder mainLibrary linuxLibrary)
	target_link_libraries(PrepareCards mainLibrary linuxLibrary)
    target_link_libraries(MatchCollector mainLibrary linuxLibrary)
    target_link_libraries(DeckRater mainLibrary linuxLibrary)
elseif(WIN32)
    target_link_libraries(DeckFinder mainLibrary winLibrary)
	target_link_libraries(PrepareCards mainLibrary winLibrary)
    target_link_libraries(MatchCollector mainLibrary winLibrary)
    target_link_libraries(DeckRater mainLibrary winLibrary)
endif()

add_subdirectory(test)
