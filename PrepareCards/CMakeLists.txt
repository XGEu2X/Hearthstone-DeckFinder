# CMakeList.txt : CMake project for DeckFinder, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (PrepareCards "PrepareCards.cpp" "PrepareCards.h")
target_link_libraries(PrepareCards mainLibrary)

# TODO: Add tests and install targets if needed.
install(TARGETS PrepareCards RUNTIME DESTINATION bin)
