find_package(SDL2)
include_directories(${SDL2_INCLUDE_DIR})


add_library(shim_sdl2 SHARED shim.cpp scaled_window.cpp)
