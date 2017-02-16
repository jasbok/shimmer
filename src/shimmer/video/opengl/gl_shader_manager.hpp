#ifndef SHIMMER_VIDEO_OPENGL_GL_SHADER_MANAGER_HPP
#define SHIMMER_VIDEO_OPENGL_GL_SHADER_MANAGER_HPP

#include "video/common/shader.hpp"
#include "video/opengl/gl_shader.hpp"
#include <GL/glew.h>
#include <memory>
#include <unordered_map>

namespace shimmer
{
class gl_shader_manager
{
public:
        gl_shader_manager();
        virtual ~gl_shader_manager();

        std::shared_ptr<shader> get ( const std::shared_ptr<shader>& shader );
private:
        std::unordered_map<std::size_t, std::shared_ptr<shader>> _shimmer_shaders;
        std::unordered_map<std::string, std::shared_ptr<gl_shader>> _gl_shaders;

        std::size_t _get_hash(const std::vector<std::vector<std::shared_ptr<gl_shader>>>& pointers);
        std::vector<std::shared_ptr<gl_shader>> _get_gl_shaders ( const std::vector<std::string>& paths, GLuint type );
};
}

#endif
