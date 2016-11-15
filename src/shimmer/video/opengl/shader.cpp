#include "shader.hpp"

shimmer::shader::shader ( GLuint program )
        : _program ( program )
{}

shimmer::shader::~shader()
{
        glDeleteProgram ( _program );
}

void shimmer::shader::use_program() const
{
        glUseProgram ( _program );
}

void shimmer::shader::reset_program() const
{
        glUseProgram ( 0 );
}

shimmer::glsl_variable shimmer::shader::attributes ( const std::string& name ) const
{
        return _attributes.at ( name );
}

shimmer::glsl_variable shimmer::shader::uniforms ( const std::string& name ) const
{
        return _uniforms.at ( name );
}

bool shimmer::shader::has_attribute ( const std::string& attr ) const
{
        return _attributes.find ( attr ) != _attributes.end();
}

bool shimmer::shader::has_uniform ( const std::string& attr ) const
{
        return _uniforms.find ( attr ) != _uniforms.end();
}

shimmer::shader& shimmer::shader::add ( const shimmer::glsl_variable& var )
{
        GLint location = -1;
        switch ( var.qualifier() ) {
        case glsl_variable::qualifier::ATTRIBUTE:
                location = glGetAttribLocation ( _program, var.name().c_str() );
                if ( location > -1 ) {
                        ( _attributes[var.name()] = var ).location ( location );
                }
                break;
        case glsl_variable::qualifier::UNIFORM:
                location = glGetUniformLocation ( _program, var.name().c_str() );
                if ( location > -1 ) {
                        ( _uniforms[var.name()] = var ).location ( location );
                }
                break;
        default:
                break;
        }

        return *this;
}

shimmer::shader& shimmer::shader::add ( const std::vector<shimmer::glsl_variable>& variables )
{
        for ( auto var : variables ) {
                add ( var );
        }
        return *this;
}
