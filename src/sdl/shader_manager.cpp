#include "shader_manager.h"
#include "config.h"
#include "file_helpers.h"
#include "opengl_helpers.h"

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

GLuint shimmer::shader_manager::create_program ( const std::vector<std::string>& vs_shaders, const std::vector<std::string>& fs_shaders )
{
        GLuint shader_program = glCreateProgram();
        GLuint vs = compile_shader ( config::instance().shaders_prefix + "/vs/" + config::instance().vertex_shader, GL_VERTEX_SHADER );
        GLuint fs = compile_shader ( config::instance().shaders_prefix + "/fs/"  + config::instance().fragment_shader, GL_FRAGMENT_SHADER );

        if ( vs && fs ) {
                std::vector<GLuint> vs_list = {vs};
                std::vector<GLuint> fs_list = {fs};

                for ( auto vs : _common_vs_compiled ) {
                        vs_list.push_back ( vs );
                }
                for ( auto fs : _common_fs_compiled ) {
                        fs_list.push_back ( fs );
                }
                link_program ( shader_program, vs_list, fs_list );

                glDetachShader ( shader_program, vs );
                glDetachShader ( shader_program, fs );
        } else {
                printf ( "==> Could not compile vs and/or fs shader.\n" );
        }

        if ( vs ) glDeleteShader ( vs );
        if ( fs ) glDeleteShader ( fs );
        return shader_program;
}


void shimmer::shader_manager::_list_shaders()
{
        _vs_shaders = list_directory ( config::instance().shaders_prefix + VS_DIR );
        _fs_shaders = list_directory ( config::instance().shaders_prefix + FS_DIR );
        _common_vs_shaders = list_directory ( config::instance().shaders_prefix + COMMON_VS_DIR );
        _common_fs_shaders = list_directory ( config::instance().shaders_prefix + COMMON_FS_DIR );
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
