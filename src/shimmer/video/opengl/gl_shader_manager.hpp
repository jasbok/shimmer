#ifndef SHIMMER_VIDEO_OPENGL_GL_SHADER_MANAGER_HPP
#define SHIMMER_VIDEO_OPENGL_GL_SHADER_MANAGER_HPP

#include "gl_shader.hpp"
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

        std::shared_ptr<shimmer::shader> get ( const std::shared_ptr<shimmer::shader>& shader );
private:
        size_t _lsize;
        GLchar* _log;

        std::unordered_map<std::size_t, std::shared_ptr<shimmer::shader>> _shimmer_shaders;
        std::unordered_map<std::string, std::shared_ptr<GLuint>> _gl_shaders;

        std::size_t _get_hash(const std::vector<std::vector<std::shared_ptr<GLuint>>>& pointers);
        std::vector<std::shared_ptr<GLuint>> _get_gl_shaders ( const std::vector<std::string>& paths, GLuint type );
        GLuint _compile_shader ( const std::vector<std::string>& sources, GLuint type );
        GLuint _link_program ( const std::vector<std::shared_ptr<GLuint>> &vs_list, const std::vector<std::shared_ptr<GLuint>> &fs_list );
};
}

#endif
