#ifndef SHIMMER_VIDEO_COMMON_SHADER_HPP
#define SHIMMER_VIDEO_COMMON_SHADER_HPP

#include "common/macros.hpp"
#include "uniform.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace shimmer
{
class shader
{
public:
    virtual ~shader() {}

    virtual void use() {}

private:
    typedef std::unordered_map<std::string, std::shared_ptr<uniform>>
            uniform_map;

    SHIMMER_MEMBER ( shader, std::vector<std::string>, fragment_shaders );

    SHIMMER_MEMBER ( shader, std::vector<std::string>, vertex_shaders );

    SHIMMER_MEMBER ( shader, uniform_map, samplers );

    SHIMMER_MEMBER ( shader, uniform_map, uniforms );
};
}

#endif
