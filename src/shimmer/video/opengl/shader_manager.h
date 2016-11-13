#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <GL/glew.h>
#include <string>
#include <vector>

namespace shimmer
{

struct variable_t
{
        std::string type;
        int size;
        std::string name;
};

typedef struct variable_t variable;

class shader_manager
{
public:
        shader_manager();
        virtual ~shader_manager();

        std::vector<std::string> vs_shaders();
        std::vector<std::string> fs_shaders();

        GLuint create_program ( const std::vector<std::string> &vs_shaders, const std::vector<std::string> &fs_shaders );
private:
        std::string _shader_dir;
        std::vector<std::string> _vs_shaders;
        std::vector<std::string> _fs_shaders;

        std::vector<std::string> _common_vs_shaders;
        std::vector<std::string> _common_fs_shaders;
        std::vector<GLuint> _common_vs_compiled;
        std::vector<GLuint> _common_fs_compiled;
private:
        void _list_shaders();
        GLuint _compile_shader ( const std::string& shader_path, GLuint type );
        std::string _remove_prepocessor_version ( const std::string& target );
        void _compile_common_shaders();
        std::vector<variable> _get_uniforms ( const std::string& source );
};
}

#endif
