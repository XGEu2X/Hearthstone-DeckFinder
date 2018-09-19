cmake_minimum_required (VERSION 3.8)

add_executable (RecursiveFiller "RecursiveFiller.cpp" "RecursiveFiller.h")
target_link_libraries(RecursiveFiller mainLibrary)


install(TARGETS RecursiveFiller RUNTIME DESTINATION bin)