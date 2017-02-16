#include "gl_shader.hpp"
#include "common/regex_helpers.hpp"
#include <iostream>

shimmer::gl_shader::gl_shader ( const std::vector<std::string>& sources, GLuint type )
        : _sources ( sources ), _type ( type )
{
        _compile();
}

shimmer::gl_shader::gl_shader ( std::vector<std::string>&& sources, GLuint type )
        : _sources ( sources ), _type ( type )
{
        _compile();
}

shimmer::gl_shader::~gl_shader()
{
        if ( _handle ) glDeleteShader ( _handle );
}

void shimmer::gl_shader::_compile ()
{
        if ( !_sources.empty() ) {
                if ( ( _handle = glCreateShader ( _type ) ) != 0 ) {
                        const GLchar** gl_sources = new const GLchar*[_sources.size()];
                        for ( unsigned int i = 0; i < _sources.size(); i++ ) {
                                gl_sources[i] = _sources[i].c_str();
                        }
                        glShaderSource ( _handle, _sources.size(), gl_sources, nullptr );
                        glCompileShader ( _handle );
                        _print_errors();
                        delete [] gl_sources;
                } else {
                        std::cerr << "Failed to create GL shader object." << std::endl;
                }
        } else {
                std::cerr << "No shader sources provided." << std::endl;
        }
}

void shimmer::gl_shader::_print_errors()
{
        GLint success;
        glGetShaderiv ( _handle, GL_COMPILE_STATUS, &success );
        if ( !success ) {
                GLchar log[512];
                glGetShaderInfoLog ( _handle, 512, nullptr, log );
                std::cerr << "Shader Compilation Failed: " << log << "\n";

                std::regex line_regex ( "\n" );
                unsigned int num = 1;
                for ( auto source : _sources ) {
                        for ( auto line : split ( source, line_regex ) ) {
                                std::cerr << num++ << ": " << line << "\n";
                        }
                }

                std::cerr << "Shader Compilation Failed: " << log << "\n";
                std::cerr << std::flush;
        }
}
