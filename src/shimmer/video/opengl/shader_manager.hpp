#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include "shader.hpp"
#include "common/types.hpp"
#include <GL/glew.h>
#include <string>
#include <vector>

namespace shimmer
{
class shader_manager
{
public:
        shader_manager();
        virtual ~shader_manager();

        std::vector<std::string> vs_shaders();
        std::vector<std::string> fs_shaders();

        shader create_shader ( const std::vector<std::string> &vs_shaders, const std::vector<std::string> &fs_shaders );
private:
        std::string _shader_dir;
        std::vector<std::string> _vs_shaders;
        std::vector<std::string> _fs_shaders;
private:
        void _list_shaders();
        std::vector<std::string> _read_sources ( const std::string& base, const std::vector<std::string>& paths );
        std::vector<GLuint> _compile_sources ( const std::vector<std::string>& sources, GLuint type );
        GLuint _link_compiled ( const std::vector<GLuint>& vs, const std::vector<GLuint>& fs );
        std::vector<glsl_variable> _read_variables ( const std::vector<std::vector<std::string>>& sources_vec );
};
}

#endif
