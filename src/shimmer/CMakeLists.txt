add_subdirectory(catch)

set(SRCS
    "common/event_system.cpp"
    "common/file_helpers.cpp"
    "common/file_utils.cpp"
    "common/regex_helpers.cpp"
    "config/config.cpp"
    "config/menu_builder.cpp"
    "font/font_face.cpp"
    "font/font_loader.cpp"
    "font/freetype.cpp"
    "input/keyboard.cpp"
    "input/mouse.cpp"
    "video/opengl/fonts/gl_font.cpp"
    "video/opengl/fonts/gl_glyph.cpp"
    "video/opengl/formats.cpp"
    "video/opengl/gl_material.cpp"
    "video/opengl/gl_material_manager.cpp"
    "video/opengl/gl_resource_manager.cpp"
    "video/opengl/gl_sampler.cpp"
    "video/opengl/gl_shader.cpp"
    "video/opengl/gl_shader_manager.cpp"
    "video/opengl/gl_program.cpp"
    "video/opengl/gl_texture.cpp"
    "video/opengl/gl_texture_manager.cpp"
    "video/opengl/gl_uniform.cpp"
    "video/opengl/glsl_variable.cpp"
    "video/opengl/opengl_helpers.cpp"
    "video/opengl/quad.cpp"
    "video/opengl/render_object.cpp"
    "video/opengl/shader.cpp"
    "video/opengl/shader_manager.cpp"
    "video/opengl/text_renderer.cpp"
    "video/opengl/texture.cpp"
    "video/opengl/uniforms/application_output.cpp"
    "video/opengl/uniforms/ticks_output.cpp"
    "video/opengl/uniforms/random_output.cpp"
    "video/opengl_renderer.cpp"
    "video/video.cpp"
    "shimmer.cpp")

add_library(shimmer SHARED ${SRCS})
target_link_libraries(shimmer ${ALL_OPENGL_LIBRARIES} ${FREETYPE_LIBRARIES})
target_include_directories(shimmer BEFORE PUBLIC "." ${FREETYPE_INCLUDE_DIRS})
install (TARGETS shimmer DESTINATION libshimmer)
