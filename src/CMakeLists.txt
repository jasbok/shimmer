add_subdirectory(shimmer)
add_subdirectory(shims)
file(COPY shaders DESTINATION .)
install(DIRECTORY shaders DESTINATION libshimmer)
