cmake_minimum_required (VERSION 3.8)

add_executable (RecursiveFiller "RecursiveFiller.cpp" "RecursiveFiller.h")
if(UNIX)
    target_link_libraries(RecursiveFiller mainLibrary linuxLibrary)
elseif(WIN32)
    target_link_libraries(RecursiveFiller mainLibrary winLibrary)
endif()

install(TARGETS RecursiveFiller RUNTIME DESTINATION bin)
