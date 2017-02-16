#ifndef SHIMMER_VIDEO_OPENGL_GL_TEXTURE_HPP
#define SHIMMER_VIDEO_OPENGL_GL_TEXTURE_HPP

#include "video/common/texture.hpp"
#include <GL/glew.h>

namespace shimmer
{
class gl_texture : public texture
{
public:
        gl_texture(const shimmer::texture& texture);
        virtual ~gl_texture();
private:
        SHIMMER_MEMBER(gl_texture, GLuint, gl_handle);
};
}

#endif
