add_subdirectory(catch)

set(SRCS 
    "api/keyboard_api.cpp"
    "api/mouse_api.cpp"
    "api/video_api.cpp"
    "api/window_api.cpp"
    "common/config.cpp"
    "common/event_system.cpp"
    "common/file_helpers.cpp"
    "common/regex_helpers.cpp"
    "input/keyboard.cpp"
    "input/mouse.cpp"
    "video/opengl/glsl_variable.cpp"
    "video/opengl/opengl_helpers.cpp"
    "video/opengl/quad.cpp"
    "video/opengl/shader.cpp"
    "video/opengl/shader_manager.cpp"
    "video/opengl/texture.cpp"
    "video/opengl_renderer.cpp"
    "video/video.cpp"
    "video/window.cpp"
    "shimmer.cpp")

add_library(shimmer SHARED ${SRCS})
target_link_libraries(shimmer ${ALL_OPENGL_LIBRARIES})
target_include_directories(shimmer BEFORE PUBLIC ".")
install (TARGETS shimmer DESTINATION libshimmer)
