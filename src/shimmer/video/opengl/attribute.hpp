#ifndef SHIMMER_VIDEO_OPENGL_ATTRIBUTE
#define SHIMMER_VIDEO_OPENGL_ATTRIBUTE

#include "common/macros.hpp"
#include <GL/glew.h>
#include <string>

namespace shimmer
{
class attribute
{
public:
        enum class type
        {
                POSITION, TEXCOORD
        };

        attribute();
        attribute ( enum type type, GLint location, const std::string& name );
        attribute ( enum type type, unsigned int size, GLint location, const std::string& name );
        virtual ~attribute();

private:
        SHIMMER_MEMBER ( attribute, enum type, type );
        SHIMMER_MEMBER ( attribute, unsigned int, size );
        SHIMMER_MEMBER ( attribute, GLint, location );
        SHIMMER_MEMBER ( attribute, std::string, name );
};
}

#endif
