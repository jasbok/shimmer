#ifndef SHIMMER_VIDEO_COMMON_SHADER_HPP
#define SHIMMER_VIDEO_COMMON_SHADER_HPP

#include "common/macros.hpp"
#include <string>
#include <vector>

namespace shimmer
{
class shader
{
public:
        shader() {}
        virtual ~shader() {}
private:
        SHIMMER_MEMBER ( shader, std::vector<std::string>, fragment_shaders );
        SHIMMER_MEMBER ( shader, std::vector<std::string>, vertex_shaders );
};
}

#endif
