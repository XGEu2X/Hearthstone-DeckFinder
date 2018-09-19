cmake_minimum_required (VERSION 3.8)

add_executable (DeckRater "DeckRater.cpp" "DeckRater.h")
target_link_libraries(DeckRater mainLibrary)

install(TARGETS DeckRater RUNTIME DESTINATION bin)