cmake_minimum_required (VERSION 3.8)

add_executable (DifferentialEvolution "DifferentialEvolution.cpp" "DifferentialEvolution.h")
if(UNIX)
    target_link_libraries(DifferentialEvolution mainLibrary linuxLibrary)
elseif(WIN32)
    target_link_libraries(DifferentialEvolution mainLibrary winLibrary)
endif()

install(TARGETS DifferentialEvolution RUNTIME DESTINATION bin)
