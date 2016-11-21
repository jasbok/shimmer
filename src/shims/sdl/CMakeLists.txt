find_package(SDL)

include_directories(${SDL_INCLUDE_DIR} "../../shimmer/")

set(SRCS 
    "event.cpp"
    "keyboard.cpp"
    "mouse.cpp"
    "shim.cpp"
    "video.cpp")

add_library(shimmer_sdl SHARED ${SRCS})
target_link_libraries(shimmer_sdl shimmer ${ALL_OPENGL_LIBRARIES})
install (TARGETS shimmer_sdl DESTINATION libshimmer)
