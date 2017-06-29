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
    "video/common/material.cpp"
    "video/common/mesh.cpp"
    "video/common/model.cpp"
    "video/common/texture.cpp"
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
    "video/video.cpp"
    "shimmer.cpp")

add_library(shimmer SHARED ${SRCS})
target_link_libraries(shimmer ${ALL_OPENGL_LIBRARIES} ${FREETYPE_LIBRARIES})
target_include_directories(shimmer BEFORE PUBLIC "." ${FREETYPE_INCLUDE_DIRS})
install (TARGETS shimmer DESTINATION libshimmer)
