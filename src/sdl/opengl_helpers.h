#ifndef OPENGL_HELPERS_H
#define OPENGL_HELPERS_H

#include "std_helpers.h"
#include <GL/glew.h>

#define GL_LOG_SIZE 512

GLuint compile_shader ( const char* source, GLuint type )
{
        static GLint SUCCESS;
        static GLchar LOG[GL_LOG_SIZE];

        GLuint shader = 0;
        std::string shader_source = read_contents ( source );

        if ( !shader_source.empty() ) {
                const GLchar* shader_source_gl = shader_source.c_str();
                shader = glCreateShader ( type );
                glShaderSource ( shader, 1, &shader_source_gl, nullptr );
                glCompileShader ( shader );
                glGetShaderiv ( shader, GL_COMPILE_STATUS, &SUCCESS );
                if ( !SUCCESS ) {
                        glGetShaderInfoLog ( shader, GL_LOG_SIZE, nullptr, LOG );
                        std::cerr << "Shader Compilation Failed: " << LOG << std::endl;
                }
        } else {
                std::cerr << "Could not read shader source: " << source << std::endl;
        }

        return shader;
}

GLuint link_program ( GLuint vs, GLuint fs )
{
        static GLint SUCCESS;
        static GLchar LOG[GL_LOG_SIZE];

        GLuint program = 0;
        if ( vs == 0 ) {
            std::cout << "Program linking failed: No vertex shader." << std::endl;
        } else if ( fs == 0 ) {
            std::cout << "Program linking failed: No fragment shader." << std::endl;
        } else {
                program = glCreateProgram();
                glAttachShader ( program, vs );
                glAttachShader ( program, fs );
                glLinkProgram ( program );
                glGetProgramiv ( program, GL_LINK_STATUS, &SUCCESS );
                if ( !SUCCESS ) {
                        glGetProgramInfoLog ( program, GL_LOG_SIZE, nullptr, LOG );
                        std::cout << "Program linking failed: " << LOG << std::endl;
                }
        }

        return program;
}


#endif
