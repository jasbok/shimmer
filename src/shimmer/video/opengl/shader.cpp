#include "shader.hpp"

shimmer::shader::shader()
{}

shimmer::shader::~shader()
{}

void shimmer::shader::use_program() const
{
        glUseProgram(_program);
}

void shimmer::shader::reset_program() const
{
        glUseProgram(0);
}
