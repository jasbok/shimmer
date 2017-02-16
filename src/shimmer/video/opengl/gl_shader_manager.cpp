#include "gl_shader_manager.hpp"
#include "common/file_utils.hpp"
#include "common/regex_helpers.hpp"
#include <iostream>

shimmer::gl_shader_manager::gl_shader_manager()
        : _lsize ( 512 ),
          _log ( new GLchar[_lsize] )
{}

shimmer::gl_shader_manager::~gl_shader_manager()
{
        delete [] _log;
}

std::shared_ptr<shimmer::shader> shimmer::gl_shader_manager::get ( const std::shared_ptr<shimmer::shader>& shader )
{
        auto vs = _get_gl_shaders ( shader->vertex_shaders(), GL_VERTEX_SHADER );
        auto fs = _get_gl_shaders ( shader->fragment_shaders(), GL_FRAGMENT_SHADER );
        auto key = _get_hash({vs, fs});
        if ( !_shimmer_shaders[key] ) {
                auto gl_shader = std::make_shared<shimmer::gl_shader> ( *shader );
                gl_shader->vs_shaders (vs);
                gl_shader->fs_shaders (fs);
                gl_shader->program ( _link_program ( gl_shader->vs_shaders(),gl_shader->fs_shaders() ) );
                _shimmer_shaders[key] = gl_shader;
        }
        return _shimmer_shaders[key];
}

std::size_t shimmer::gl_shader_manager::_get_hash(const std::vector<std::vector<std::shared_ptr<GLuint> > >& pointers)
{
        std::size_t h;
        for(auto y : pointers){
                for(auto x : y){
                        h = std::hash<std::shared_ptr<GLuint>>{}(x) ^ (h << 1);
                }
        }
        return h;
}

std::vector<std::shared_ptr<GLuint>> shimmer::gl_shader_manager::_get_gl_shaders ( const std::vector<std::string>& paths, GLuint type )
{
        std::vector<std::shared_ptr<GLuint>> shaders;
        for(auto path : paths){
                if ( !_gl_shaders[path] ) {
                _gl_shaders[path] = std::make_shared<GLuint> ( _compile_shader ( { file_utils::read_contents ( path ) }, type ) );
        }
                shaders.push_back(_gl_shaders[path]);
        }
        return shaders;
}

GLuint shimmer::gl_shader_manager::_compile_shader ( const std::vector<std::string>& sources, GLuint type )
{
        GLuint shader = 0;
        GLint success = 0;

        if ( !sources.empty() ) {
                if ( ( shader = glCreateShader ( type ) ) != 0 ) {
                        const GLchar** gl_sources = new const GLchar*[sources.size()];
                        for ( unsigned int i = 0; i < sources.size(); i++ ) {
                                gl_sources[i] = sources[i].c_str();
                        }

                        glShaderSource ( shader, sources.size(), gl_sources, nullptr );
                        glCompileShader ( shader );
                        glGetShaderiv ( shader, GL_COMPILE_STATUS, &success );
                        if ( !success ) {
                                std::regex line_regex ( "\n" );
                                glGetShaderInfoLog ( shader, _lsize, nullptr, _log );
                                std::cerr << "Shader Compilation Failed: " << _log << "\n";
                                unsigned int num = 1;
                                for ( auto source : sources ) {
                                        for ( auto line : split ( source, line_regex ) ) {
                                                std::cerr << num++ << ": " << line << "\n";
                                        }
                                }
                                std::cerr << "Shader Compilation Failed: " << _log << "\n";
                                std::cerr << std::flush;
                        }
                        delete [] gl_sources;
                } else {
                        std::cerr << "Failed to create GL shader object." << std::endl;
                }
        } else {
                std::cerr << "No shader sources provided." << std::endl;
        }

        return shader;
}

GLuint shimmer::gl_shader_manager::_link_program ( const std::vector<std::shared_ptr<GLuint>> &vs_list, const std::vector<std::shared_ptr<GLuint>> &fs_list )
{
        GLuint program = 0;
        GLint success = 0;

        if ( vs_list.empty() ) {
                std::cout << "Program linking failed: No vertex shaders in list." << std::endl;
        } else if ( fs_list.empty() ) {
                std::cout << "Program linking failed: No fragment shaders in list." << std::endl;
        } else if ( ( program = glCreateProgram() ) != 0 ) {
                for ( auto vs : vs_list ) {
                        glAttachShader ( program, *vs );
                }
                for ( auto fs : fs_list ) {
                        glAttachShader ( program, *fs );
                }
                glLinkProgram ( program );
                glGetProgramiv ( program, GL_LINK_STATUS, &success );
                if ( !success ) {
                        glGetProgramInfoLog ( program, _lsize, nullptr, _log );
                        std::cout << "Program linking failed: " << _log << std::endl;
                }
        } else {
                std::cerr << "Failed to create GL program object." << std::endl;
        }
        return program;
}

