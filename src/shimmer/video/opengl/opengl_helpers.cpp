#include "opengl_helpers.hpp"
#include "common/file_helpers.hpp"
#include "common/regex_helpers.hpp"

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
                for ( unsigned int i = 0; i < sources.size(); i++ ) {
                        gl_sources[i] = sources[i].c_str();
                }
                shader = glCreateShader ( type );
                glShaderSource ( shader, sources.size(), gl_sources, nullptr );
                glCompileShader ( shader );
                glGetShaderiv ( shader, GL_COMPILE_STATUS, &SUCCESS );
                if ( !SUCCESS ) {
                        glGetShaderInfoLog ( shader, BUFFER_SIZE, nullptr, LOG );
                        std::cerr << "Shader Compilation Failed: " << LOG << std::endl;
                        for ( auto source : sources ) {
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

void detachShaders ( GLuint program, const std::vector<std::vector<GLuint>>& shaders_vec )
{
        for ( auto shaders : shaders_vec ) {
                for ( auto s : shaders ) {
                        glDetachShader ( program, s );
                }
        }
}

void deleteShaders ( const std::vector<std::vector<GLuint>>& shaders_vec )
{
        for ( auto shaders : shaders_vec ) {
                for ( auto s : shaders ) {
                        glDeleteShader ( s );
                }
        }
}

std::unordered_map<std::string, variable<>> read_variables ( const std::string var_keyword, const std::vector<std::string>& sources )
{
        std::unordered_map<std::string, variable<>> results;
        std::regex regex ( var_keyword + "\\s+(\\w*)\\s*(\\[(\\d)+\\])?\\s+([\\w]+).*?;" );
        for ( auto source : sources ) {
                for ( auto uniform : find_all ( source, regex, {1, 3, 4} ) ) {
                        results[uniform[0]] = variable<> ( uniform[0], uniform[1].empty() ? 0 : std::stoi ( uniform[1] ), uniform[2] );
                }
        }
        return results;
}

std::unordered_map<std::string, std::unordered_map<std::string, variable<>>> read_variables ( const std::vector<std::vector<std::string>>& sources_vec )
{
        std::unordered_map<std::string, std::unordered_map<std::string, variable<>>> results;
        std::regex regex ( "\\s+(\\w*)\\s+(\\w*)\\s*(\\[(\\d)+\\])?\\s+([\\w]+).*?;" );
        for ( auto sources : sources_vec ) {
                for ( auto source : sources ) {
                        for ( auto uniform : find_all ( source, regex, {1, 3, 4} ) ) {
                                results[uniform[0]][uniform[1]] = variable<> ( uniform[1], uniform[2].empty() ? 0 : std::stoi ( uniform[2] ), uniform[3] );
                        }
                }
        }
        return results;
}

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
