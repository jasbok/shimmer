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
        texture(dimensions<GLint> dims, unsigned int bpp, GLenum pixel_format, GLenum pixel_type);
        virtual ~texture();

        void setup();
        void pixels ( void* pixels );

        void* map_buffer();
        void unmap_buffer();
private:
        GLuint _pbo[2];
        int _pbo_index;
        unsigned int _buffer_size;
        void* _data;

        SHIMMER_GETTER ( texture, GLuint, gl_texture);
        SHIMMER_MEMBER ( texture, dimensions<GLint>, dims );
        SHIMMER_MEMBER ( texture, unsigned int, bpp );
        SHIMMER_MEMBER ( texture, GLenum, filter );
        SHIMMER_MEMBER ( texture, GLenum, internal_format );
        SHIMMER_MEMBER ( texture, GLenum, pixel_format );
        SHIMMER_MEMBER ( texture, GLenum, pixel_type );
};
}

#endif
