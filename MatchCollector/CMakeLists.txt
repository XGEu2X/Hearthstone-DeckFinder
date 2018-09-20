# CMakeList.txt : CMake project for DeckFinder, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (MatchCollector "MatchCollector.cpp" "MatchCollector.h")
if(UNIX)
    target_link_libraries(MatchCollector mainLibrary linuxLibrary)
elseif(WIN32)
    target_link_libraries(MatchCollector mainLibrary winLibrary)
endif()
    
# TODO: Add tests and install targets if needed.
install(TARGETS MatchCollector RUNTIME DESTINATION bin)
