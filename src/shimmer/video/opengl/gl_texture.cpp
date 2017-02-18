#include "gl_texture.hpp"
#include <GL/glew.h>
#include <cstring>

namespace shimmer
{
gl_texture::gl_texture(const texture& texture, unsigned int pbo_count)
        : _pbo_count(pbo_count)
{
        _extend(texture);
        _create();
}

gl_texture::~gl_texture()
{
        if(_gl_handle) glDeleteTextures(1, &_gl_handle);
        if(_gl_pbo){
                glDeleteBuffers(_pbo_count, _gl_pbo);
                delete [] _gl_pbo;
        }
}

texture &gl_texture::filter(const enum texture::filter &filter)
{
        texture::filter(filter);
        _update_filter();
        return *this;
}

texture &gl_texture::filter(enum texture::filter &&filter)
{
        texture::filter(filter);
        _update_filter();
        return *this;
}

void gl_texture::pixels(void *pixels, unsigned int w, unsigned int h, unsigned int x, unsigned int y)
{
        auto data = ( GLubyte* ) _map_buffer();
        if(data){
                if(w && h){
                        unsigned int x_offset = x * _bytes_per_pixel;
                        unsigned int y_offset = y;
                        unsigned int range_width = w * _bytes_per_pixel;
                        unsigned int texture_width = width() * _bytes_per_pixel;
                        for ( unsigned int y = 0; y < h; y++ ) {
                                std::memcpy ( data + y * range_width, ( GLubyte* ) pixels + ( y + y_offset ) * texture_width + x_offset, range_width );
                        }
                        _unmap_buffer ( x, y, w, h );
                }
                else{
                        std::memcpy ( data, pixels, _size );
                        _unmap_buffer(0, 0, width(), height());
                }
        }
}

void gl_texture::_extend(const texture &texture)
{
        id(texture.id());
        width(texture.width());
        height(texture.height());

        access(texture.access());
        filter(texture.filter());
        format(texture.format());
        internal(texture.internal());
        type(texture.type());
}

void gl_texture::_create()
{
        auto filter = _gl_filter();
        _bytes_per_pixel = _bpp_from(format());
        _size = width() * height() * _bytes_per_pixel;

        glGenTextures ( 1, &_gl_handle );
        glBindTexture ( GL_TEXTURE_2D, _gl_handle );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexImage2D ( GL_TEXTURE_2D,
                       0,
                       _gl_internal(),
                       width(),
                       height(),
                       0,
                       _gl_format(),
                       _gl_type(),
                       0 );
        glBindTexture ( GL_TEXTURE_2D, 0 );

        if(access() == texture::access::STREAMING){
                _gl_pbo = new GLuint[_pbo_count];
                glGenBuffers ( _pbo_count, _gl_pbo );
        }
}

unsigned int gl_texture::_next_pbo(){
        _curr_pbo++;
        _curr_pbo = _curr_pbo < _pbo_count ? _curr_pbo : 0;
        return _gl_pbo[_curr_pbo];
}

void * gl_texture::_map_buffer()
{
        if(_gl_pbo){
                glBindBuffer ( GL_PIXEL_UNPACK_BUFFER, _next_pbo() );
                glBufferData ( GL_PIXEL_UNPACK_BUFFER, _size, 0, GL_STREAM_DRAW );
                return glMapBuffer ( GL_PIXEL_UNPACK_BUFFER,  GL_WRITE_ONLY );
        }
        return nullptr;
}

void gl_texture::_unmap_buffer ( unsigned int w, unsigned int h, unsigned int x, unsigned int y )
{
        glUnmapBuffer ( GL_PIXEL_UNPACK_BUFFER );
        glBindTexture ( GL_TEXTURE_2D, _gl_handle );
        glTexSubImage2D ( GL_TEXTURE_2D,
                          0,
                          x, y, w, h,
                          _gl_format(),
                          _gl_type(),
                          0 );

        glBindTexture ( GL_TEXTURE_2D, 0 );
        glBindBuffer ( GL_PIXEL_UNPACK_BUFFER, 0 );
}

void gl_texture::_update_filter()
{
        if(_gl_handle){
                auto filter = _gl_filter();
                glBindTexture ( GL_TEXTURE_2D, _gl_handle );
                glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter );
                glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter );
                glBindTexture ( GL_TEXTURE_2D, 0 );
        }
}

GLenum gl_texture::_gl_filter()
{
        return _gl_enum_from(texture::filter());
}

GLenum gl_texture::_gl_format()
{
        return _gl_enum_from(format());
}

GLenum gl_texture::_gl_internal()
{
        return _gl_enum_from(internal());
}

GLenum gl_texture::_gl_type()
{
        return _gl_enum_from(type());
}

GLenum gl_texture::_gl_enum_from(enum texture::filter filter)
{
        switch(filter) {
        case texture::filter::NEAREST:
                return GL_NEAREST;
        case texture::filter::LINEAR:
                return GL_LINEAR;
        }
        return GL_NEAREST;
}

GLenum gl_texture::_gl_enum_from(enum texture::format format)
{
        switch ( format ) {
        case texture::format::RGB:
                return GL_RGB;
        case texture::format::BGR:
                return GL_BGR;
        case texture::format::RGBA:
                return GL_RGBA;
        case texture::format::BGRA:
                return GL_BGRA;
        case texture::format::RGB_INTEGER:
                return GL_RGB_INTEGER;
        case texture::format::BGR_INTEGER:
                return GL_BGR_INTEGER;
        case texture::format::RGBA_INTEGER:
                return GL_RGBA_INTEGER;
        case texture::format::BGRA_INTEGER:
                return GL_BGRA_INTEGER;
        }
        return GL_BGRA;
}

GLenum gl_texture::_gl_enum_from(enum texture::type type)
{
        switch ( type ) {
        case texture::type::BYTE:
                return GL_BYTE;
        case texture::type::UNSIGNED_BYTE:
                return GL_UNSIGNED_BYTE;
        case texture::type::UNSIGNED_SHORT_5_6_5:
                return GL_UNSIGNED_SHORT_5_6_5;
        case texture::type::UNSIGNED_SHORT_5_6_5_REV:
                return GL_UNSIGNED_SHORT_5_6_5_REV;
        }
        return GL_UNSIGNED_BYTE;
}

GLenum gl_texture::_gl_enum_from(enum texture::internal internal)
{
        switch(internal) {
        case texture::internal::RGB:
                return GL_RGB;
        case texture::internal::RGBA:
                return GL_RGBA;
        }
        return GL_RGBA;
}

unsigned int gl_texture::_bpp_from(enum texture::format format)
{
        // TODO: Find actual size of integer formats.
        switch(format){
        case format::RGB:
        case format::BGR:
        case format::RGB_INTEGER:
        case format::BGR_INTEGER:
                return 3;
        case format::RGBA:
        case format::BGRA:
        case format::RGBA_INTEGER:
        case format::BGRA_INTEGER:
                return 4;
        }
        return 3;
}

}
