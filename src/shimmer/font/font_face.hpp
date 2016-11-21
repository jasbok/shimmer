#ifndef SHIMMER_FONT_FONT_FACE_HPP
#define SHIMMER_FONT_FONT_FACE_HPP

#include "freetype.hpp"

namespace shimmer
{
class font_face
{
public:
        font_face ( FT_Face face, unsigned int font_size );
        font_face ( font_face&& move );
        virtual ~font_face();

        void operator= ( font_face&& move );
        FT_Face operator->() const;

        FT_GlyphSlot glyph ( unsigned int code );
        FT_GlyphSlot operator[] ( unsigned int code );
private:
        FT_Face _face;
        unsigned int _font_size;
private:
        font_face ( const font_face& copy );
        void operator= ( const font_face& copy );
};
}

#endif
