find_package(SDL2)
include_directories(${SDL2_INCLUDE_DIR} "../../shimmer/")

set(SRCS 
    "event.cpp"
    "gl.cpp"
    "keyboard.cpp"
    "mouse.cpp"
    "shim.cpp"
    "video.cpp")

#add_library(shimmer_sdl2 SHARED ${SRCS})
#target_link_libraries(shimmer_sdl2 shimmer ${ALL_OPENGL_LIBRARIES})
#install (TARGETS shimmer_sdl2 DESTINATION libshimmer)
