#ifndef SHIMMER_VIDEO_OPENGL_GL_SHADER_HPP
#define SHIMMER_VIDEO_OPENGL_GL_SHADER_HPP

#include "common/macros.hpp"
#include <GL/glew.h>
#include <string>
#include <vector>

namespace shimmer
{
class gl_shader
{
public:
        gl_shader(const std::vector<std::string>& sources, GLuint type);
        gl_shader(std::vector<std::string>&& sources, GLuint type);
        virtual ~gl_shader();
private:
        SHIMMER_GETTER ( gl_shader, std::vector<std::string> , sources);
        SHIMMER_GETTER ( gl_shader, GLuint , type);
        SHIMMER_GETTER ( gl_shader, GLuint, handle );

        void _compile();
        void _print_errors();
};
}

#endif
