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

void link_program ( GLuint program, GLuint vs, GLuint fs )
{
    static GLint SUCCESS;
    static GLchar LOG[GL_LOG_SIZE];

    if(program == 0){
        std::cout << "Program linking failed: Program has not been created." << std::endl;
    }
    if ( vs == 0 ) {
        std::cout << "Program linking failed: No vertex shader." << std::endl;
    } else if ( fs == 0 ) {
        std::cout << "Program linking failed: No fragment shader." << std::endl;
    } else {
        glAttachShader ( program, vs );
        glAttachShader ( program, fs );
        glLinkProgram ( program );
        glGetProgramiv ( program, GL_LINK_STATUS, &SUCCESS );
        if ( !SUCCESS ) {
            glGetProgramInfoLog ( program, GL_LOG_SIZE, nullptr, LOG );
            std::cout << "Program linking failed: " << LOG << std::endl;
        }
    }
}

#define PRINT_GL_ERROR_ENUM(ENUM) printf("(%s:%u) GL Error: ENUM.\n", file, line)
#define PRINT_GL_ERROR() print_gl_error(__FILE__, __LINE__)


// void print_gl_error(const char* file, int line) {
//     switch(glGetError()) {
//     case GL_INVALID_ENUM:
//         PRINT_GL_ERROR_ENUM(GL_INVALID_ENUM);
//         break;
//     case GL_INVALID_VALUE:
//         PRINT_GL_ERROR_ENUM(GL_INVALID_VALUE);
//         break;
//     case GL_INVALID_OPERATION:
//         PRINT_GL_ERROR_ENUM(GL_INVALID_OPERATION);
//         break;
//     case GL_INVALID_FRAMEBUFFER_OPERATION:
//         PRINT_GL_ERROR_ENUM(GL_INVALID_FRAMEBUFFER_OPERATION);
//         break;
//     case GL_OUT_OF_MEMORY:
//         PRINT_GL_ERROR_ENUM(GL_OUT_OF_MEMORY);
//         break;
//     case GL_STACK_UNDERFLOW:
//         PRINT_GL_ERROR_ENUM(GL_STACK_UNDERFLOW);
//         break;
//     case GL_STACK_OVERFLOW:
//         PRINT_GL_ERROR_ENUM(GL_STACK_OVERFLOW);
//         break;
//     default:
//         break;
//     }
// }

int print_gl_error(const char* file, int line) {
    switch(glGetError()) {
    case GL_INVALID_ENUM:
        printf("(%s:%u) GL Error: GL_INVALID_ENUM.\n", file, line);
        break;
    case GL_INVALID_VALUE:
        printf("(%s:%u) GL Error: GL_INVALID_VALUE.\n", file, line);
        break;
    case GL_INVALID_OPERATION:
        printf("(%s:%u) GL Error: GL_INVALID_OPERATION.\n", file, line);
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        printf("(%s:%u) GL Error: GL_INVALID_FRAMEBUFFER_OPERATION.\n", file, line);
        break;
    case GL_OUT_OF_MEMORY:
        printf("(%s:%u) GL Error: GL_OUT_OF_MEMORY.\n", file, line);
        break;
    case GL_STACK_UNDERFLOW:
        printf("(%s:%u) GL Error: GL_STACK_UNDERFLOW.\n", file, line);
        break;
    case GL_STACK_OVERFLOW:
        printf("(%s:%u) GL Error: GL_STACK_OVERFLOW.\n", file, line);
        break;
    default:
        return 0;
        break;
    }
    
    return 1;
}
#endif
