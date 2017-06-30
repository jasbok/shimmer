#include "texture.hpp"

#include <cstring>

namespace shimmer
{
texture::texture()
    : _pbo(),
      _pbo_index ( 0 ),
      _data ( nullptr ),
      _dims (),
      _bpp ( 32 ),
      _internal_format ( GL_RGB ),
      _pixel_format ( GL_BGRA ),
      _pixel_type ( GL_UNSIGNED_BYTE ),
      _filter ( GL_LINEAR )
{
    glGenTextures ( 1, &_gl_texture );
    glGenBuffers ( 2, _pbo );
    setup();
}

texture::texture (
    dimensions<GLuint> dims,
    unsigned int bpp, GLenum
    pixel_format,
    GLenum pixel_type )
    :_pbo(),
     _pbo_index ( 0 ),
     _data ( nullptr ),
     _dims ( dims ),
     _bpp ( bpp ),
     _internal_format ( GL_RGB ),
     _pixel_format ( pixel_format ),
     _pixel_type ( pixel_type ),
     _filter ( GL_LINEAR )
{
    glGenTextures ( 1, &_gl_texture );
    glGenBuffers ( 2, _pbo );
    setup();
}


texture::~texture()
{
    glDeleteTextures ( 1, &_gl_texture );
    glDeleteBuffers ( 2, _pbo );
}

void texture::setup()
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

    _buffer_stride = _dims.w * _bpp * 0.125;
    _buffer_size = _dims.h * _buffer_stride;
}

void texture::pixels ( void* pixels )
{
    _data = ( GLubyte* ) map_buffer();
    if ( _data ) {
        std::memcpy ( _data, pixels, _buffer_size );
        unmap_buffer();
    } else {
        printf ( "Unable to map PBO buffer.\n" );
    }
}

void texture::pixels (
    void* pixels,
    const rectangle<coordinates<GLuint>,
    dimensions<GLuint> >& rect )
{
    _data = ( GLubyte* ) map_buffer();
    if ( _data ) {
        unsigned int bytes_per_pixel = _bpp * 0.125;
        unsigned int x_offset = rect.coords.x * bytes_per_pixel;
        unsigned int range_width = rect.dims.w * bytes_per_pixel;
        unsigned int width = _dims.w * bytes_per_pixel;

        for ( unsigned int y = 0; y < rect.dims.h; y++ ) {
            auto start = _data + y * range_width;

            auto offset = ( GLubyte* ) pixels
                          + ( y + rect.coords.y )
                          * width
                          * + x_offset;

            std::memcpy ( start, offset, range_width );
        }

        _unmap_buffer ( rect );
    } else {
        printf ( "Unable to map PBO buffer.\n" );
    }
}

void* texture::map_buffer()
{
    _pbo_index = !_pbo_index;
    glBindBuffer ( GL_PIXEL_UNPACK_BUFFER, _pbo[_pbo_index] );
    glBufferData ( GL_PIXEL_UNPACK_BUFFER, _buffer_size, 0, GL_STREAM_DRAW );
    return glMapBuffer ( GL_PIXEL_UNPACK_BUFFER,  GL_WRITE_ONLY );
}

void texture::unmap_buffer()
{
    _unmap_buffer ( {{0, 0}, _dims} );
}

texture& texture::filter ( GLenum filter )
{
    _filter = filter;
    glBindTexture ( GL_TEXTURE_2D, _gl_texture );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filter );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filter );
    glBindTexture ( GL_TEXTURE_2D, 0 );
    return *this;
}

void texture::_unmap_buffer (
    const rectangle<coordinates<GLuint>,
    dimensions<GLuint>>& rect )
{
    glUnmapBuffer ( GL_PIXEL_UNPACK_BUFFER );
    glBindTexture ( GL_TEXTURE_2D, _gl_texture );
    glTexSubImage2D ( GL_TEXTURE_2D,
                      0,
                      rect.coords.x,
                      rect.coords.y,
                      rect.dims.w,
                      rect.dims.h,
                      _pixel_format,
                      _pixel_type,
                      0 );

    glBindTexture ( GL_TEXTURE_2D, 0 );
    glBindBuffer ( GL_PIXEL_UNPACK_BUFFER, 0 );
}
}
