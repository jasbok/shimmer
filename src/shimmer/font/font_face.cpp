#include "font_face.hpp"
#include <iostream>

shimmer::font_face::font_face ( FT_Face face, unsigned int font_size )
        :_face ( face ), _font_size ( font_size )
{
        FT_Set_Pixel_Sizes ( _face, 0, _font_size );
}

shimmer::font_face::font_face ( shimmer::font_face && move )
        : _face ( move._face )
{
        move._face = nullptr;
}

shimmer::font_face::~font_face()
{
        if ( _face ) {
                FT_Done_Face ( _face );
        }
}

void shimmer::font_face::operator= ( shimmer::font_face && move )
{
        this->_face = move._face;
        move._face = nullptr;
}

FT_Face shimmer::font_face::operator->() const
{
        return _face;
}

FT_GlyphSlot shimmer::font_face::glyph ( unsigned int code )
{
        FT_Error error = FT_Load_Char ( _face, code, FT_LOAD_RENDER );
        if ( error ) {
                std::cerr << "Unable to load glyph ( " << code << " -> " << ( char ) code << "): " << freetype_string_from ( error ) << "." << std::endl;
        }
        return _face->glyph;
}

FT_GlyphSlot shimmer::font_face::operator[] ( unsigned int code )
{
        return glyph ( code );
}

bool shimmer::font_face::has_kerning()
{
        return FT_HAS_KERNING(_face);
}

shimmer::coordinates<int> shimmer::font_face::kern_distance(unsigned int left, unsigned int right)
{
        FT_Vector vec;
        FT_Get_Kerning(_face, left, right, FT_KERNING_DEFAULT, &vec);
        return coordinates<int>(vec.x, vec.y);
}
