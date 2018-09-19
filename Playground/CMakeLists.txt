cmake_minimum_required (VERSION 3.8)

add_executable (Playground "Playground.cpp" "Playground.h")
target_link_libraries(Playground mainLibrary)


install(TARGETS Playground RUNTIME DESTINATION bin)