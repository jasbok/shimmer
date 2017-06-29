find_package(SDL)

include_directories(${SDL_INCLUDE_DIR} "../../shimmer/")

set(SRCS 
    "event.cpp"
    "gl.cpp"
    "keyboard.cpp"
    "mouse.cpp"
    "shim.cpp"
    "video.cpp")

message(SDL_LIBRARY: ${SDL_LIBRARY})

#add_library(shimmer_sdl SHARED ${SRCS})
#target_link_libraries(shimmer_sdl shimmer ${SDL_LIBRARY} ${ALL_OPENGL_LIBRARIES})
#install (TARGETS shimmer_sdl DESTINATION libshimmer)
