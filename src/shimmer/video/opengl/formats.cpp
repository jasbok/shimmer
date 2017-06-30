#include "formats.hpp"

namespace shimmer{
GLenum gl_formats::pixel_format_from(pixel_format format)
{
        GLenum pixel_format = GL_BGRA;

        switch ( format ) {
        case pixel_format::RGB:
                pixel_format = GL_RGB;
                break;
        case pixel_format::BGR:
                pixel_format = GL_BGR;
                break;
        case pixel_format::BGRA:
                pixel_format = GL_BGRA;
                break;
        default:
                break;
        }

        return pixel_format;
}

GLenum gl_formats::pixel_type_from(pixel_type type)
{
        GLenum pixel_type = GL_UNSIGNED_BYTE;

        switch ( type ) {
        case pixel_type::UNSIGNED_SHORT_5_6_5:
                pixel_type = GL_UNSIGNED_SHORT_5_6_5;
                break;
        case pixel_type::UNSIGNED_BYTE:
                pixel_type = GL_UNSIGNED_BYTE;
                break;
        default:
                break;
        }

        return pixel_type;
}
}
