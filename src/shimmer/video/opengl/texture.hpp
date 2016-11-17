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
        void pixels ( void* pixels );
        void bind();
        void unbind();
private:
        GLuint _texture;
        GLuint _pbo[2];
        int _pbo_index;
        GLenum _unit;

        SHIMMER_MEMBER ( texture, dimensions<GLint>, dims );
        SHIMMER_MEMBER ( texture, unsigned int, bpp );
        SHIMMER_MEMBER ( texture, GLenum, filter );
        SHIMMER_MEMBER ( texture, GLenum, pixel_format );
        SHIMMER_MEMBER ( texture, GLenum, pixel_type );
        SHIMMER_MEMBER ( texture, GLenum, texunit );
        SHIMMER_MEMBER ( texture, GLint, location );
private:
        GLint _uniform_value_from_unit();
};
}

#endif
