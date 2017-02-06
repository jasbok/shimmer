#include "gl_font.hpp"
#include "../opengl_helpers.hpp"

shimmer::gl_font::gl_font()
        : _textures ( new GLuint[128] ),
          _kern_distances ( 128 * 128 )
{

}

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
                delete [] _textures;
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

void shimmer::gl_font::font_face ( shimmer::font_face& face )
{
        unsigned int range = 128;
        if ( !_glyphs.empty() ) {
                glDeleteTextures ( _glyphs.size(), _textures );
                _glyphs.clear();
        }

        glGenTextures ( range, _textures );
        _glyphs.reserve ( range );

        for ( unsigned int c = 0; c < range; c++ ) {
                auto g = face[c];
                auto glyph = gl_glyph();
                if ( g->bitmap.width > 0 && g->bitmap.rows > 0 && g->bitmap.buffer != nullptr ) {
                        glyph
                             .dims ( dimensions<GLuint> ( g->bitmap.width, g->bitmap.rows ) )
                             .bearing ( coordinates<GLint> ( g->bitmap_left, g->bitmap_top ) )
                             .advance ( g->advance.x >> 6 )
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
                }
                _glyphs.push_back ( glyph );
        }
        if ( face.has_kerning() ) {
                for ( unsigned int j = 0; j < range; j++ ) {
                        for ( unsigned int i = 0; i < range; i++ ) {
                                _kern_distances[j * range + i] = face.kern_distance ( i, j );
                        }
                }
        }
}

shimmer::gl_glyph& shimmer::gl_font::glyph ( unsigned char c )
{
        return _glyphs[c < _glyphs.size() ? c : 0];
}

shimmer::coordinates<int> shimmer::gl_font::kern ( unsigned char left, unsigned char right )
{
        return _kern_distances[right * 128 + left];
}
