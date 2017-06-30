#ifndef SHIMMER_VIDEO_OPENGL_FONT_GL_GLYPH_HPP
#define SHIMMER_VIDEO_OPENGL_FONT_GL_GLYPH_HPP

#include "common/types.hpp"
#include "common/macros.hpp"
#include <GL/glew.h>

namespace shimmer
{
class gl_glyph
{
private:
    SHIMMER_MEMBER ( gl_glyph, GLint, texture );
    SHIMMER_MEMBER ( gl_glyph, coordinates<GLint>, bearing );
    SHIMMER_MEMBER ( gl_glyph, dimensions<GLuint>, dims );
    SHIMMER_MEMBER ( gl_glyph, GLint, advance );
};
}

#endif
