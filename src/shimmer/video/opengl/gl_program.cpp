#include "gl_program.hpp"
#include <iostream>

namespace shimmer
{
gl_program::gl_program (
        const shader& shader,
        const gl_shaders& gl_vertex_shaders,
        const gl_shaders& gl_fragment_shaders )
        : _gl_vertex_shaders ( gl_vertex_shaders ),
          _gl_fragment_shaders ( gl_fragment_shaders )
{
        _extend(shader);
        _link_program();
}

gl_program::gl_program (
        const shader& shader,
        gl_shaders && gl_vertex_shaders,
        gl_shaders && gl_fragment_shaders )
        : _gl_vertex_shaders ( gl_vertex_shaders ),
          _gl_fragment_shaders ( gl_fragment_shaders )
{
        _extend(shader);
        _link_program();
}

gl_program::~gl_program()
{
        if ( _handle ) glDeleteProgram ( _handle );
}

void gl_program::use()
{
        glUseProgram(_handle);
}

void gl_program::_extend ( const shader& shader )
{
        vertex_shaders ( shader.vertex_shaders() );
        fragment_shaders ( shader.fragment_shaders() );
        samplers ( shader.samplers() );
        uniforms ( shader.uniforms() );
}

std::vector<gl_program::gl_shaders> gl_program::_all_shaders()
{
        return {
                _gl_vertex_shaders, _gl_fragment_shaders
        };
}

void gl_program::_link_program ()
{
        if ( _gl_vertex_shaders.empty() ) {
                std::cout << "Program linking failed: No vertex shaders in list." << std::endl;
        } else if ( _gl_fragment_shaders.empty() ) {
                std::cout << "Program linking failed: No fragment shaders in list." << std::endl;
        } else if ( ( _handle = glCreateProgram() ) != 0 ) {
                for(auto group : _all_shaders()) {
                        for(auto shader : group) {
                                glAttachShader ( _handle, shader->handle() );
                                _parse_variables(shader);
                        }
                }
                glLinkProgram ( _handle );
                _print_errors();
        } else {
                std::cerr << "Failed to create GL program object." << std::endl;
        }
}

void gl_program::_parse_variables(const std::shared_ptr<gl_shader> &shader)
{
        for(auto variable : shader->variables()) {
                switch(variable.qualifier()) {
                case glsl_variable::qualifier::UNIFORM:
                        switch(variable.type()) {
                        case glsl_variable::type::ISAMPLER1D:
                        case glsl_variable::type::ISAMPLER2D:
                        case glsl_variable::type::ISAMPLER3D:
                        case glsl_variable::type::SAMPLER1D:
                        case glsl_variable::type::SAMPLER2D:
                        case glsl_variable::type::SAMPLER3D:
                                // TODO
                                break;
                        default:
                                break;
                        }
                        break;
                case glsl_variable::qualifier::ATTRIBUTE:
                case glsl_variable::qualifier::VARYING:
                case glsl_variable::qualifier::UNKNOWN:
                        break;
                }
        }
}

void gl_program::_print_errors()
{
        GLint success = 0;
        glGetProgramiv ( _handle, GL_LINK_STATUS, &success );
        if ( !success ) {
                GLchar log[512];
                glGetProgramInfoLog ( _handle, 512, nullptr, log );
                std::cout << "Program linking failed: " << log << std::endl;
        }
}
}
