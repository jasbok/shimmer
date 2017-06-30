#include "shader.hpp"

namespace shimmer
{
shader::shader ( GLuint program )
    : _program ( program )
{}

shader::~shader()
{
    glDeleteProgram ( _program );
}

shader& shader::use_program()
{
    glUseProgram ( _program );
    print_gl_error ( __FILE__, __LINE__ );
    for ( auto uniform_output : _uniform_outputs ) {
        uniform_output->process();
        print_gl_error ( __FILE__, __LINE__ );
    }
    return *this;
}

void shader::use_program() const
{
    glUseProgram ( _program );
    for ( auto uniform_output : _uniform_outputs ) {
        uniform_output->process();
    }
}

void shader::reset_program() const
{
    glUseProgram ( 0 );
}

glsl_variable shader::attributes ( const std::string& name ) const
{
    return _attributes.at ( name );
}

glsl_variable shader::uniforms ( const std::string& name ) const
{
    return _uniforms.at ( name );
}

bool shader::has_attribute ( const std::string& attr ) const
{
    auto a = _attributes.find ( attr );

    return a != _attributes.end() && a->second.location() != -1;
}

bool shader::has_uniform ( const std::string& attr ) const
{
    auto u = _uniforms.find ( attr );

    return u != _uniforms.end() && u->second.location() != -1;
}

shader& shader::add ( const glsl_variable& var )
{
    switch ( var.qualifier() ) {
    case glsl_variable::qualifier::ATTRIBUTE:
        _attributes[var.name()] = var;
        break;

    case glsl_variable::qualifier::UNIFORM:
        _uniforms[var.name()] = var;
        break;

    default:
        break;
    }

    return *this;
}

shader& shader::add ( const std::vector<glsl_variable>& variables )
{
    for ( auto var : variables ) {
        add ( var );
    }

    return *this;
}
}
