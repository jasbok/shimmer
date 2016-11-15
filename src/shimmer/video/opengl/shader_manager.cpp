#include "shader_manager.hpp"
#include "opengl_helpers.hpp"
#include "common/config.hpp"
#include "common/file_helpers.hpp"
#include "common/regex_helpers.hpp"

shimmer::shader_manager::shader_manager ()
{
        _list_shaders();
}

shimmer::shader_manager::~shader_manager()
{}

std::vector<std::string> shimmer::shader_manager::vs_shaders()
{
        return _vs_shaders;
}

std::vector<std::string> shimmer::shader_manager::fs_shaders()
{
        return _fs_shaders;
}

shimmer::shader shimmer::shader_manager::create_shader ( const std::vector<std::string>& vs_in, const std::vector<std::string>& fs_in )
{
        auto vs_sources = _read_sources ( config::instance().shaders_prefix + "/vs/", vs_in );
        auto fs_sources = _read_sources ( config::instance().shaders_prefix + "/fs/", fs_in );
        auto vs_compiled = compile_shader ( vs_sources, GL_VERTEX_SHADER );
        auto fs_compiled = compile_shader ( fs_sources, GL_FRAGMENT_SHADER );
        auto program = _link_compiled ( {vs_compiled}, {fs_compiled} );
        auto variables = _read_variables ( {vs_sources, fs_sources} );
        deleteShaders ( {{vs_compiled}, {fs_compiled}} );

        shader shader ( program );
        shader.add ( variables );
        return shader;
}


void shimmer::shader_manager::_list_shaders()
{
        _vs_shaders = list_directory ( config::instance().shaders_prefix + "/vs" );
        _fs_shaders = list_directory ( config::instance().shaders_prefix + "/fs" );
}

std::vector<std::string> shimmer::shader_manager::_read_sources ( const std::string& base, const std::vector<std::string>& paths )
{
        std::vector<std::string> sources;
        std::regex version_regex ( "\\s*#version\\s\\d{3}\\s*" );
        sources.push_back ( "#version 130\n" );
        for ( auto path : paths ) {
                std::string source = std::regex_replace ( read_contents ( base + path ), version_regex , "" );
                sources.push_back ( source );
                if ( !source.empty() ) {
                        std::regex include_regex ( "\\s*\\/{2}\\s*#include\\s+([\\w.\\/\\\\]*)\\s*" );
                        for ( auto include : find_all ( source, include_regex, 1 ) ) {
                                std::string include_source = read_contents ( config::instance().shaders_prefix + "/" + include );
                                sources.push_back ( std::regex_replace ( include_source, version_regex , "" ) );
                        }
                }
        }
        return sources;
}

std::vector<GLuint> shimmer::shader_manager::_compile_sources ( const std::vector<std::string>& sources, GLuint type )
{
        std::vector<GLuint> compiled_sources;
        for ( auto source : sources ) {
                compile_shader ( source, type );
        }
        return compiled_sources;
}

GLuint shimmer::shader_manager::_link_compiled ( const std::vector<GLuint>& vs, const std::vector<GLuint>& fs )
{
        GLuint program = 0;
        if ( !vs.empty() && !fs.empty() ) {
                program = glCreateProgram();
                link_program ( program, vs, fs );
                detachShaders ( program, {vs, fs} );
        } else {
                printf ( "==> Could not link vs and/or fs shader(s).\n" );
        }
        return program;
}

std::vector<shimmer::glsl_variable> shimmer::shader_manager::_read_variables ( const std::vector<std::vector<std::string>>& sources_vec )
{
        // 0:qualifier 1:type 2:size 3:name
        std::regex regex ( "\\s*(\\w+)\\s+(\\w+)\\s*(\\[(\\d)+\\])?\\s+([\\w]+).*?;" );
        std::vector<glsl_variable> results;
        for ( auto sources : sources_vec ) {
                for ( auto source : sources ) {
                        for ( auto var : find_all ( source, regex, {1, 2, 4, 5} ) ) {
                                results.push_back (
                                        glsl_variable (
                                                glsl_variable::qualifier_from ( var[0] ),
                                                glsl_variable::type_from ( var[1] ),
                                                var[2].empty() ? 1 : std::stoi ( var[2] ),
                                                var[3] ) );
                        }
                }
        }
        return results;
}
