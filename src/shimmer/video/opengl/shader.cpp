#include "shader.hpp"

shimmer::shader::shader()
{}

shimmer::shader::~shader()
{
        glDeleteProgram( _program );
}

void shimmer::shader::use_program() const
{
        glUseProgram ( _program );
}

void shimmer::shader::reset_program() const
{
        glUseProgram ( 0 );
}

shimmer::attribute shimmer::shader::attributes(const std::string& name) const
{
        return _variables.at("attribute").at(name);
}

shimmer::attribute shimmer::shader::uniforms(const std::string& name) const
{
        return _variables.at("uniform").at(name);
}

bool shimmer::shader::has_attribute(const std::string& attr) const
{
        return _variables.find("attribute") != _variables.end() && _variables.at("attribute").find(attr) != _variables.at("attribute").end();
}

bool shimmer::shader::has_uniform(const std::string& attr) const
{
        return _variables.find("uniform") != _variables.end() && _variables.at("uniform").find(attr) != _variables.at("uniform").end();
}
