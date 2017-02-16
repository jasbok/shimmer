#include "gl_shader.hpp"

shimmer::gl_shader::gl_shader ( const shimmer::shader& shader )
{
        vertex_shaders(shader.vertex_shaders());
        fragment_shaders(shader.fragment_shaders());
}

shimmer::gl_shader::~gl_shader() {}
