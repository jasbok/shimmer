find_package(SDL)

include_directories(${SDL_INCLUDE_DIR} )

set(SRCS 
    "sdl_shim.cpp"
    "shimmer.cpp"
    "hw_surface.cpp"
    "shader_manager.cpp"
    "opengl_helpers.cpp"
    "file_helpers.cpp")

add_library(shimmer SHARED ${SRCS})
target_link_libraries(shimmer ${ALL_OPENGL_LIBRARIES})
install (TARGETS shimmer DESTINATION libshimmer)
