find_package(SDL)

include_directories(${SDL_INCLUDE_DIR} ) 
set(SRCS "sdl_shim.cpp" "shimmer.cpp" "sw_surface.cpp" "hw_surface.cpp" "sw_scaler.cpp")

add_library(shimmer SHARED ${SRCS})
target_link_libraries(shimmer ${ALL_OPENGL_LIBRARIES})
