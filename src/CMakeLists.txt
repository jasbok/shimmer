add_subdirectory(sdl)
add_subdirectory(sdl2)

file(COPY shaders DESTINATION .)
install(DIRECTORY shaders DESTINATION libshimmer)
