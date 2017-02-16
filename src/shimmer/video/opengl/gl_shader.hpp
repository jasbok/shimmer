#ifndef SHIMMER_VIDEO_OPENGL_GL_SHADER_HPP
#define SHIMMER_VIDEO_OPENGL_GL_SHADER_HPP

#include "video/common/shader.hpp"
#include <GL/glew.h>
#include <memory>
#include <vector>

namespace shimmer
{
class gl_shader : public shader {
public:
        gl_shader(const shader& shader);
        virtual ~gl_shader();
private:
        typedef std::vector<std::shared_ptr<GLuint>> compiled_shaders;
        SHIMMER_MEMBER ( shader, GLuint, program );
        SHIMMER_MEMBER ( shader, compiled_shaders, fs_shaders );
        SHIMMER_MEMBER ( shader, compiled_shaders, vs_shaders );
};
}

#endif
