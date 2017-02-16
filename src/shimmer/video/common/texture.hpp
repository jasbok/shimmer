#ifndef SHIMMER_VIDEO_COMMON_TEXTURE_HPP
#define SHIMMER_VIDEO_COMMON_TEXTURE_HPP

#include "common/macros.hpp"
#include <string>

namespace shimmer
{
class texture
{
public:
        texture() {}
        virtual ~texture() {}
private:
        SHIMMER_MEMBER ( texture, std::string, path );
};
}

#endif
