#ifndef SHIMMER_VIDEO_OPENGL_FORMATS
#define SHIMMER_VIDEO_OPENGL_FORMATS

#include "common/enums.hpp"
#include <GL/glew.h>

namespace shimmer
{
class gl_formats
{
public:
    static GLenum pixel_format_from ( shimmer::pixel_format format );
    static GLenum pixel_type_from ( shimmer::pixel_type type );
};
}

#endif
