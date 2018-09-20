cmake_minimum_required (VERSION 3.8)

add_executable (Playground "Playground.cpp" "Playground.h")
if(UNIX)
    target_link_libraries(Playground mainLibrary linuxLibrary)
elseif(WIN32)
    target_link_libraries(Playground mainLibrary winLibrary)
endif()

install(TARGETS Playground RUNTIME DESTINATION bin)
