#include "gl_font.hpp"

shimmer::gl_font::gl_font()
{}

shimmer::gl_font::gl_font ( shimmer::gl_font && move )
        : _textures ( move._textures ), _glyphs ( std::move ( move._glyphs ) )
{
        move._textures = nullptr;
        move._glyphs.clear();
}

shimmer::gl_font::~gl_font()
{
        if ( _textures ) {
                glDeleteTextures ( _glyphs.size(), _textures );
        }
}

void shimmer::gl_font::operator= ( shimmer::gl_font && move )
{
        this->_textures = move._textures;
        this->_glyphs = std::move ( move._glyphs );
        move._textures = nullptr;
        move._glyphs.clear();
}

shimmer::gl_glyph& shimmer::gl_font::operator[] ( unsigned char c )
{
        return glyph ( c );
}

void shimmer::gl_font::font_face ( shimmer::font_face && face, unsigned int range )
{
        if ( !_glyphs.empty() ) {
                glDeleteTextures ( _glyphs.size(), _textures );
                _glyphs.clear();
        }

        glGenTextures ( range, _textures );
        _glyphs.reserve ( range );

        for ( unsigned int c = 0; c < range; c++ ) {
                auto g = face[c];
                auto glyph = gl_glyph()
                             .dims ( {static_cast<GLuint> ( g->metrics.width ), static_cast<GLuint> ( g->metrics.height ) } )
                             .bearing ( { static_cast<GLint> ( g->metrics.horiBearingX ), static_cast<GLint> ( g->metrics.horiBearingY ) } )
                             .advance ( g->advance.x )
                             .texture ( _textures[c] );

                glBindTexture ( GL_TEXTURE_2D, _textures[c] );
                glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
                glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
                glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
                glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
                glTexImage2D ( GL_TEXTURE_2D,
                               0,
                               GL_RED,
                               glyph.dims().w,
                               glyph.dims().h,
                               0,
                               GL_RED,
                               GL_UNSIGNED_BYTE,
                               g->bitmap.buffer );
                glBindTexture ( GL_TEXTURE_2D, 0 );

                _glyphs.push_back ( glyph );
        }
}

shimmer::gl_glyph& shimmer::gl_font::glyph ( unsigned char c )
{
        return _glyphs[c < _glyphs.size() ? c : 0];
}
