#include "shader_manager.h"
#include "config.h"
#include "file_helpers.h"
#include "opengl_helpers.h"
#include "regex_helpers.h"

#define VS_DIR "/vs"
#define FS_DIR "/fs"
#define COMMON_VS_DIR "/common/vs"
#define COMMON_FS_DIR "/common/fs"

shimmer::shader_manager::shader_manager ()
{
        _list_shaders();
        _compile_common_shaders();
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

GLuint shimmer::shader_manager::create_program ( const std::vector<std::string>& vs_in, const std::vector<std::string>& fs_in )
{
        GLuint shader_program = glCreateProgram();
        std::vector<GLuint> vs_list = {};
        std::vector<GLuint> fs_list = {};

        for ( auto vs : vs_in ) {
                GLuint compiled = _compile_shader ( config::instance().shaders_prefix + "/vs/" + vs, GL_VERTEX_SHADER );
                if ( compiled ) vs_list.push_back ( compiled );
        }
        for ( auto fs : fs_in ) {
                GLuint compiled = _compile_shader ( config::instance().shaders_prefix + "/fs/"  + fs, GL_FRAGMENT_SHADER );
                if ( compiled ) fs_list.push_back ( compiled );
        }

        if ( !vs_list.empty() && !fs_list.empty() ) {
                link_program ( shader_program, vs_list, fs_list );
                detachShaders ( shader_program, vs_list );
                detachShaders ( shader_program, fs_list );
        } else {
                printf ( "==> Could not compile vs and/or fs shader(s).\n" );
        }

        deleteShaders ( vs_list );
        deleteShaders ( fs_list );

        return shader_program;
}


void shimmer::shader_manager::_list_shaders()
{
        _vs_shaders = list_directory ( config::instance().shaders_prefix + VS_DIR );
        _fs_shaders = list_directory ( config::instance().shaders_prefix + FS_DIR );
        _common_vs_shaders = list_directory ( config::instance().shaders_prefix + COMMON_VS_DIR );
        _common_fs_shaders = list_directory ( config::instance().shaders_prefix + COMMON_FS_DIR );
}

GLuint shimmer::shader_manager::_compile_shader ( const std::string& shader_path , GLuint type )
{
        std::string shader_source = _remove_prepocessor_version ( read_contents ( shader_path ) );
        std::vector<std::string> sources;
        if ( !shader_source.empty() ) {
                sources.push_back ( "#version 130\n" );
                for ( auto include : find_all ( shader_source, std::regex ( "\\s*\\/{2}\\s*#include\\s+([\\w.\\/\\\\]*)\\s*" ), 1 ) ) {
                        sources.push_back ( _remove_prepocessor_version ( read_contents ( config::instance().shaders_prefix + "/" + include ) ) );
                }
                sources.push_back ( shader_source );
        }
        for ( auto uniform : _get_uniforms(shader_source) ) {
                printf ( "==> Active Uniforms: %s[%i] %s\n", uniform.type.c_str(), uniform.size, uniform.name.c_str() );
        }
        return compile_shader ( sources, type );
}

std::string shimmer::shader_manager::_remove_prepocessor_version ( const std::string& target )
{
        return std::regex_replace ( target, std::regex ( "\\s*#version\\s\\d{3}\\s*" ), "" );
}

void shimmer::shader_manager::_compile_common_shaders()
{
        for ( auto vs : _common_vs_shaders ) {
                GLuint vs_compiled = compile_shader ( config::instance().shaders_prefix + COMMON_VS_DIR + "/" + vs, GL_VERTEX_SHADER );
                if ( vs_compiled ) {
                        _common_vs_compiled.push_back ( vs_compiled );
                }
        }

        for ( auto fs : _common_fs_shaders ) {
                GLuint fs_compiled = compile_shader ( config::instance().shaders_prefix + COMMON_FS_DIR + "/" + fs, GL_FRAGMENT_SHADER );
                if ( fs_compiled ) {
                        _common_fs_compiled.push_back ( fs_compiled );
                }
        }
}

std::vector<shimmer::variable> shimmer::shader_manager::_get_uniforms ( const std::string& source )
{
        std::vector<variable> results;
        for ( auto uniform : find_all ( source, std::regex ( "uniform\\s+(\\w*)\\s*(\\[(\\d)+\\])?\\s+([\\w]+).*?;" ), {1, 3, 4} ) ) {
                results.push_back ( variable {uniform[0], uniform[1].empty() ? 0 : std::stoi ( uniform[1] ), uniform[2]} );
        }
        return results;
}
