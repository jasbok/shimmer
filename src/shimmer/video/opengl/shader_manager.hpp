#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include "shader.hpp"
#include "common/types.hpp"
#include "uniforms/uniform_output.hpp"
#include "texture.hpp"
#include <GL/glew.h>
#include <memory>
#include <string>
#include <vector>

namespace shimmer
{
class shader_manager
{
public:
        shader_manager();
        virtual ~shader_manager();

        std::shared_ptr<shader> create ( const std::vector<std::string> &vs_shaders, const std::vector<std::string> &fs_shaders );
private:
        SHIMMER_MEMBER(shader_manager, std::string, shader_dir);
        SHIMMER_MEMBER(shader_manager, std::shared_ptr<texture>, application_texture);
        SHIMMER_GETTER(shader_manager, std::vector<std::string>, vs_shaders);
        SHIMMER_GETTER(shader_manager, std::vector<std::string>, fs_shaders);

        enum class shimmer_uniforms
        {
                APPLICATION_OUTPUT,
                RANDOM,
                TICKS
        };
        static std::unordered_map<std::string, enum shimmer_uniforms> _uniform_map;

private:
        void _list_shaders();
        std::vector<std::string> _read_sources ( const std::string& base, const std::vector<std::string>& paths );
        std::vector<GLuint> _compile_sources ( const std::vector<std::string>& sources, GLuint type );
        GLuint _link_compiled ( const std::vector<GLuint>& vs, const std::vector<GLuint>& fs );
        std::vector<glsl_variable> _read_variables ( const std::vector<std::vector<std::string>>& sources_vec, GLuint program );
        std::shared_ptr<uniform_output> _uniform_output_from ( const glsl_variable& variable );
        std::vector<std::shared_ptr<uniform_output>> _create_uniform_outputs(const std::vector<glsl_variable>& uniforms);
};
}

#endif
