#ifndef SHIMMER_VIDEO_OPENGL_TEXTURE_HPP
#define SHIMMER_VIDEO_OPENGL_TEXTURE_HPP

#include "common/types.hpp"
#include "common/macros.hpp"
#include <GL/glew.h>

namespace shimmer
{
class texture
{
public:
        texture();
        texture ( dimensions<GLuint> dims, unsigned int bpp, GLenum pixel_format, GLenum pixel_type );
        virtual ~texture();

        void setup();
        void pixels ( void* pixels );
        void pixels ( void* pixels, const rectangle<coordinates<GLuint>, dimensions<GLuint>>& rect );

        void* map_buffer();
        void unmap_buffer();

        texture& filter(GLenum filter);
private:
        GLuint _pbo[2];
        int _pbo_index;
        unsigned int _buffer_size;
        unsigned int _buffer_stride;
        GLubyte* _data;

        SHIMMER_MEMBER ( texture, dimensions<GLuint>, dims );
        SHIMMER_MEMBER ( texture, unsigned int, bpp );
        SHIMMER_MEMBER ( texture, GLenum, internal_format );
        SHIMMER_MEMBER ( texture, GLenum, pixel_format );
        SHIMMER_MEMBER ( texture, GLenum, pixel_type );
        SHIMMER_GETTER ( texture, GLuint, gl_texture );
        SHIMMER_GETTER ( texture, GLenum, filter );

private:
        void _unmap_buffer ( const rectangle<coordinates<GLuint>, dimensions<GLuint>>& rect );
};
}

#endif
