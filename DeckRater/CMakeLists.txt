cmake_minimum_required (VERSION 3.8)

add_executable (DeckRater "DeckRater.cpp" "DeckRater.h")
if(UNIX)
    target_link_libraries(DeckRater mainLibrary linuxLibrary)
elseif(WIN32)
    target_link_libraries(DeckRater mainLibrary winLibrary)
endif()

install(TARGETS DeckRater RUNTIME DESTINATION bin)
