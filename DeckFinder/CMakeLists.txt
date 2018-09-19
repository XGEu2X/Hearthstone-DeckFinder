cmake_minimum_required (VERSION 3.8)

add_executable (DifferentialEvolution "DifferentialEvolution.cpp" "DifferentialEvolution.h")
target_link_libraries(DifferentialEvolution mainLibrary)


install(TARGETS DifferentialEvolution RUNTIME DESTINATION bin)