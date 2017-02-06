#ifndef SHIMMER_VIDEO_SHADER_HPP
#define SHIMMER_VIDEO_SHADER_HPP

#include "common/macros.hpp"
#include <string>
#include <vector>

namespace shimmer
{
class shader
{
public:

private:
        SHIMMER_MEMBER ( shader, std::string, vs_path );
        SHIMMER_MEMBER ( shader, std::string, fs_path );
};
}

#endif
