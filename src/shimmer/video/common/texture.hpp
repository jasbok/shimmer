#ifndef SHIMMER_VIDEO_COMMON_TEXTURE_HPP
#define SHIMMER_VIDEO_COMMON_TEXTURE_HPP

#include "common/macros.hpp"
#include <string>

namespace shimmer
{
class texture
{
public:
    texture();

    texture ( const std::string& id );

    texture ( std::string&& id );

    texture ( unsigned int width, unsigned int height );

    texture ( const std::string& id, unsigned int width, unsigned int height );

    texture ( std::string&& id, unsigned int width, unsigned int height );

    virtual ~texture() {}

    enum class access
    {
        STATIC, STREAMING
    };

    enum class filter
    {
        NEAREST, LINEAR
    };

    enum class format
    {
        RGB, BGR, RGBA, BGRA,
        RGB_INTEGER, BGR_INTEGER, RGBA_INTEGER, BGRA_INTEGER
    };

    enum class internal
    {
        RGB, RGBA
    };

    enum class type
    {
        BYTE, UNSIGNED_BYTE, UNSIGNED_SHORT_5_6_5, UNSIGNED_SHORT_5_6_5_REV
    };

    virtual void pixels (
        void* pixels,
        unsigned int w = 0,
        unsigned int h = 0,
        unsigned int x = 0,
        unsigned int y = 0 ) = 0;

    virtual void bind() {}

private:
    SHIMMER_MEMBER ( texture, std::string, id );

    SHIMMER_MEMBER ( texture, enum access, access );

    SHIMMER_MEMBER ( texture, enum filter, filter );

    SHIMMER_MEMBER ( texture, enum format, format );

    SHIMMER_MEMBER ( texture, enum internal, internal );

    SHIMMER_MEMBER ( texture, enum type, type );

    SHIMMER_MEMBER ( texture, unsigned int, width );

    SHIMMER_MEMBER ( texture, unsigned int, height );
};
}

#endif
