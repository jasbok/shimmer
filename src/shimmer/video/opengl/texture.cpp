#include "texture.hpp"

#include <cstring>

shimmer::texture::texture()
        : _bpp ( 32 ),
          _internal_format ( GL_RGB ),
          _pixel_format ( GL_BGRA ),
          _pixel_type ( GL_UNSIGNED_BYTE )
{
        glGenTextures ( 1, &_gl_texture );
        glGenBuffers ( 2, _pbo );
        setup();
}

shimmer::texture::texture (
        dimensions<GLint> dims,
        unsigned int bpp, GLenum
        pixel_format,
        GLenum pixel_type )
        : _dims ( dims ),
          _bpp ( bpp ),
          _internal_format ( GL_RGB ),
          _pixel_format ( pixel_format ),
          _pixel_type ( pixel_type )
{
        glGenTextures ( 1, &_gl_texture );
        glGenBuffers ( 2, _pbo );
        setup();
}


shimmer::texture::~texture()
{
        glDeleteTextures ( 1, &_gl_texture );
        glDeleteBuffers ( 2, _pbo );
}

void shimmer::texture::setup()
{
        glBindTexture ( GL_TEXTURE_2D, _gl_texture );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filter );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filter );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexImage2D ( GL_TEXTURE_2D,
                       0,
                       _internal_format,
                       _dims.w,
                       _dims.h,
                       0,
                       _pixel_format,
                       _pixel_type,
                       0 );
        glBindTexture ( GL_TEXTURE_2D, 0 );
}

void shimmer::texture::pixels ( void* pixels )
{
        unsigned int buffer_size = _dims.w * _dims.h * _bpp * 0.125;
        _pbo_index = !_pbo_index;
        glBindBuffer ( GL_PIXEL_UNPACK_BUFFER, _pbo[_pbo_index] );
        glBufferData ( GL_PIXEL_UNPACK_BUFFER, buffer_size, 0, GL_STREAM_DRAW );
        GLubyte* data_ptr = ( GLubyte* ) glMapBuffer ( GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY );
        if ( data_ptr ) {
                std::memcpy ( data_ptr, pixels, buffer_size );

                glUnmapBuffer ( GL_PIXEL_UNPACK_BUFFER );

                glBindTexture ( GL_TEXTURE_2D, _gl_texture );
                glTexSubImage2D ( GL_TEXTURE_2D,
                                  0,
                                  0,
                                  0,
                                  _dims.w,
                                  _dims.h,
                                  _pixel_format,
                                  _pixel_type,
                                  0 );

                glBindTexture ( GL_TEXTURE_2D, 0 );
        } else {
                printf ( "Unable to map PBO buffer.\n" );
        }
        glBindBuffer ( GL_PIXEL_UNPACK_BUFFER, 0 );
}
