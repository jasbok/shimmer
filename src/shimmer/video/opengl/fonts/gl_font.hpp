#ifndef SHIMMER_VIDEO_OPENGL_FONTS_GL_FONT_HPP
#define SHIMMER_VIDEO_OPENGL_FONTS_GL_FONT_HPP

#include "gl_glyph.hpp"
#include "font/font_face.hpp"
#include <vector>

namespace shimmer
{
class gl_font
{
public:
        gl_font();
        gl_font ( const gl_font& copy ) = delete;
        gl_font ( gl_font&& move );
        virtual ~gl_font();

        void operator= ( const gl_font& copy ) = delete;
        void operator= ( gl_font&& move );
        gl_glyph& operator[] ( unsigned char c );

        void font_face ( font_face&& face, unsigned int range );
        gl_glyph& glyph ( unsigned char c );
private:
        GLuint* _textures;
        std::vector<gl_glyph> _glyphs;
};
}

#endif
