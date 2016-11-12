add_subdirectory(catch)

set(SRCS 
    "config.cpp"
    "input/keyboard.cpp"
    "input/mouse.cpp"
    "video/video.cpp"
    "video/window.cpp"
    "event_system.cpp"
    "keyboard_system.cpp"
    "mouse_system.cpp"
    "video_system.cpp"
    "window_system.cpp"
    "shimmer.cpp")

add_library(shimmer SHARED ${SRCS})
target_link_libraries(shimmer ${ALL_OPENGL_LIBRARIES})
install (TARGETS shimmer DESTINATION libshimmer)
