#include "opengl_helpers.h"
#include "file_helpers.h"

#define BUFFER_SIZE 512

namespace shimmer
{
GLuint compile_shader ( const char* source, GLuint type )
{
        static GLint SUCCESS;
        static GLchar LOG[BUFFER_SIZE];

        GLuint shader = 0;
        std::string shader_source = read_contents ( source );

        if ( !shader_source.empty() ) {
                const GLchar* shader_source_gl = shader_source.c_str();
                shader = glCreateShader ( type );
                glShaderSource ( shader, 1, &shader_source_gl, nullptr );
                glCompileShader ( shader );
                glGetShaderiv ( shader, GL_COMPILE_STATUS, &SUCCESS );
                if ( !SUCCESS ) {
                        glGetShaderInfoLog ( shader, BUFFER_SIZE, nullptr, LOG );
                        std::cerr << "Shader Compilation Failed (" << source << "): " << LOG << std::endl;
                }
        } else {
                std::cerr << "Could not read shader source: " << source << std::endl;
        }

        return shader;
}

GLuint compile_shader ( const std::string& source, GLuint type )
{
        return compile_shader ( source.c_str(), type );
}

GLuint compile_shader ( const std::vector<std::string>& sources, GLuint type )
{
        static GLint SUCCESS;
        static GLchar LOG[BUFFER_SIZE];

        GLuint shader = 0;

        if ( !sources.empty() ) {
                const GLchar** gl_sources = new const GLchar*[sources.size()];
                for(unsigned int i = 0; i < sources.size(); i++){
                        gl_sources[i] = sources[i].c_str();
                }
                shader = glCreateShader ( type );
                glShaderSource ( shader, sources.size(), gl_sources, nullptr );
                glCompileShader ( shader );
                glGetShaderiv ( shader, GL_COMPILE_STATUS, &SUCCESS );
                if ( !SUCCESS ) {
                        glGetShaderInfoLog ( shader, BUFFER_SIZE, nullptr, LOG );
                        std::cerr << "Shader Compilation Failed: " << LOG << std::endl;
                        for(auto source : sources){
                                std::cerr << source << std::endl;
                        }
                }
                delete [] gl_sources;
        } else {
                std::cerr << "No shader sources provided." << std::endl;
        }

        return shader;
}

void link_program ( GLuint program, GLuint vs, GLuint fs )
{
        static GLint SUCCESS;
        static GLchar LOG[BUFFER_SIZE];

        if ( program == 0 ) {
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
                        glGetProgramInfoLog ( program, BUFFER_SIZE, nullptr, LOG );
                        std::cout << "Program linking failed: " << LOG << std::endl;
                }
        }
}

void link_program ( GLuint program, const std::vector<GLuint> &vs_list, const std::vector<GLuint> &fs_list )
{
        static GLint SUCCESS;
        static GLchar LOG[BUFFER_SIZE];

        if ( program == 0 ) {
                std::cout << "Program linking failed: Program has not been created." << std::endl;
        }
        if ( vs_list.empty() ) {
                std::cout << "Program linking failed: No vertex shaders in list." << std::endl;
        } else if ( fs_list.empty() ) {
                std::cout << "Program linking failed: No fragment shaders in list." << std::endl;
        } else {
                for ( auto vs : vs_list ) {
                        glAttachShader ( program, vs );
                }
                for ( auto fs : fs_list ) {
                        glAttachShader ( program, fs );
                }
                glLinkProgram ( program );
                glGetProgramiv ( program, GL_LINK_STATUS, &SUCCESS );
                if ( !SUCCESS ) {
                        glGetProgramInfoLog ( program, BUFFER_SIZE, nullptr, LOG );
                        std::cout << "Program linking failed: " << LOG << std::endl;
                }
        }
}

void detachShaders ( GLuint program, const std::vector<GLuint>& shaders )
{
        for ( auto s : shaders ) {
                glDetachShader ( program, s );
        }
}

void deleteShaders ( const std::vector<GLuint>& shaders )
{
        for ( auto s : shaders ) {
                glDeleteShader ( s );
        }
}

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
//         PRINT_GL_ERROR_ENUM(GL_STACK_OVERFLOaW);
//         break;
//     default:
//         break;
//     }
// }

int print_gl_error ( const char* file, int line )
{
        GLenum error = glGetError();
        switch ( error ) {
        case GL_INVALID_ENUM:
                printf ( "(%s:%u) GL Error: GL_INVALID_ENUM.\n", file, line );
                break;
        case GL_INVALID_VALUE:
                printf ( "(%s:%u) GL Error: GL_INVALID_VALUE.\n", file, line );
                break;
        case GL_INVALID_OPERATION:
                printf ( "(%s:%u) GL Error: GL_INVALID_OPERATION.\n", file, line );
                break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
                printf ( "(%s:%u) GL Error: GL_INVALID_FRAMEBUFFER_OPERATION.\n", file, line );
                break;
        case GL_OUT_OF_MEMORY:
                printf ( "(%s:%u) GL Error: GL_OUT_OF_MEMORY.\n", file, line );
                break;
        case GL_STACK_UNDERFLOW:
                printf ( "(%s:%u) GL Error: GL_STACK_UNDERFLOW.\n", file, line );
                break;
        case GL_STACK_OVERFLOW:
                printf ( "(%s:%u) GL Error: GL_STACK_OVERFLOW.\n", file, line );
                break;
        default:
                return 0;
                break;
        }

        return 1;
}
}
