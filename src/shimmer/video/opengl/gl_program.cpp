#include "gl_program.hpp"
#include <iostream>

shimmer::gl_program::gl_program (
        const shader& shader,
        const gl_shaders& gl_vertex_shaders,
        const gl_shaders& gl_fragment_shaders )
        : _gl_vertex_shaders ( gl_vertex_shaders ),
          _gl_fragment_shaders ( gl_fragment_shaders )
{
        _extend(shader);
        _link_program();
}

shimmer::gl_program::gl_program (
        const shader& shader,
        gl_shaders && gl_vertex_shaders,
        gl_shaders && gl_fragment_shaders )
        : _gl_vertex_shaders ( gl_vertex_shaders ),
          _gl_fragment_shaders ( gl_fragment_shaders )
{
        _extend(shader);
        _link_program();
}


shimmer::gl_program::~gl_program()
{
        if ( _handle ) glDeleteProgram ( _handle );
}

void shimmer::gl_program::_extend ( const shimmer::shader& shader )
{
        vertex_shaders ( shader.vertex_shaders() );
        fragment_shaders ( shader.fragment_shaders() );
}

void shimmer::gl_program::_link_program ()
{
        if ( _gl_vertex_shaders.empty() ) {
                std::cout << "Program linking failed: No vertex shaders in list." << std::endl;
        } else if ( _gl_fragment_shaders.empty() ) {
                std::cout << "Program linking failed: No fragment shaders in list." << std::endl;
        } else if ( ( _handle = glCreateProgram() ) != 0 ) {
                for ( auto vs : _gl_vertex_shaders ) {
                        glAttachShader ( _handle, vs->handle() );
                }
                for ( auto fs : _gl_fragment_shaders ) {
                        glAttachShader ( _handle, fs->handle() );
                }
                glLinkProgram ( _handle );

                GLint success = 0;
                glGetProgramiv ( _handle, GL_LINK_STATUS, &success );
                if ( !success ) {
                        GLchar log[512];
                        glGetProgramInfoLog ( _handle, 512, nullptr, log );
                        std::cout << "Program linking failed: " << log << std::endl;
                }
        } else {
                std::cerr << "Failed to create GL program object." << std::endl;
        }
}

