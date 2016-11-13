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
        virtual ~texture();

        void setup();
        void data ( void* pixels, unsigned int w, unsigned int h, unsigned int bpp );
        void bind();
        void unbind();
private:
        SHIMMER_MEMBER ( texture, dimensions<GLint>, dims );
        SHIMMER_MEMBER ( texture, unsigned int, bpp );
        SHIMMER_MEMBER ( texture, GLenum, filter );
        SHIMMER_MEMBER ( texture, GLenum, pixel_format );
        SHIMMER_MEMBER ( texture, GLenum, pixel_type );
        GLuint _texture;
        GLuint *_pbo;
        int _pbo_index;
};
}

#endif
