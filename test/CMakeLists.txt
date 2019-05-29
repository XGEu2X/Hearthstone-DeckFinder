cmake_minimum_required (VERSION 3.8)

add_executable(Playground "Playground.cpp")
target_link_libraries(Playground mainLibrary winLibrary)