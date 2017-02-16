#include "gl_texture.hpp"

shimmer::gl_texture::gl_texture(const shimmer::texture& texture)
{
        id(texture.id());
        path(texture.path());
        width(texture.width());
        height(texture.height());
}

shimmer::gl_texture::~gl_texture()
{
        glDeleteTextures(1, &_gl_handle);
}
