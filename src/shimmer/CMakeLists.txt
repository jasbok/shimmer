add_subdirectory(catch)

set(SRCS 
    "common/config.cpp"
    "common/event_system.cpp"
    "common/file_helpers.cpp"
    "common/regex_helpers.cpp"
    "input/keyboard.cpp"
    "input/mouse.cpp"
    "video/opengl/formats.cpp"
    "video/opengl/glsl_variable.cpp"
    "video/opengl/opengl_helpers.cpp"
    "video/opengl/quad.cpp"
    "video/opengl/render_object.cpp"
    "video/opengl/shader.cpp"
    "video/opengl/shader_manager.cpp"
    "video/opengl/texture.cpp"
    "video/opengl/uniforms/application_output.cpp"
    "video/opengl/uniforms/ticks_output.cpp"
    "video/opengl/uniforms/random_output.cpp"
    "video/opengl_renderer.cpp"
    "video/video.cpp"
    "shimmer.cpp")

add_library(shimmer SHARED ${SRCS})
target_link_libraries(shimmer ${ALL_OPENGL_LIBRARIES})
target_include_directories(shimmer BEFORE PUBLIC ".")
install (TARGETS shimmer DESTINATION libshimmer)
