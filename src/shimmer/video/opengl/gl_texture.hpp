#ifndef SHIMMER_VIDEO_OPENGL_GL_TEXTURE_HPP
#define SHIMMER_VIDEO_OPENGL_GL_TEXTURE_HPP

#include "video/common/texture.hpp"
#include <GL/glew.h>

namespace shimmer
{
class gl_texture : public texture
{
public:
        gl_texture(const texture& texture, unsigned int pbo_count);
        virtual ~gl_texture();

        virtual texture& filter(const enum texture::filter& filter);
        virtual texture& filter(enum texture::filter&& filter);

        virtual void pixels (
                void* pixels,
                unsigned int w = 0,
                unsigned int h = 0,
                unsigned int x = 0,
                unsigned int y = 0);

private:
        SHIMMER_MEMBER(gl_texture, GLuint, gl_handle);
        GLuint* _gl_pbo;
        unsigned int _pbo_count, _curr_pbo;
        unsigned int _bytes_per_pixel;
        unsigned int _size;

        void _create();
        void _extend(const texture& texture);
        void _update_filter();

        GLenum _gl_filter();
        GLenum _gl_format();
        GLenum _gl_internal();
        GLenum _gl_type();
        GLenum _gl_enum_from(enum texture::filter filter);
        GLenum _gl_enum_from(enum texture::format format);
        GLenum _gl_enum_from(enum texture::internal internal);
        GLenum _gl_enum_from(enum texture::type type);
        unsigned int _bpp_from(enum texture::format format);
        void _unmap_buffer(unsigned int w, unsigned int h, unsigned int x, unsigned int y);
        void *_map_buffer();
        unsigned int _next_pbo();
};
}

#endif
