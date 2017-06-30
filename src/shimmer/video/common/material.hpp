#ifndef SHIMMER_VIDEO_COMMON_MATERIAL_HPP
#define SHIMMER_VIDEO_COMMON_MATERIAL_HPP

#include "common/macros.hpp"
#include "sampler.hpp"
#include "shader.hpp"
#include "uniform.hpp"
#include <memory>
#include <vector>

namespace shimmer
{
class material
{
public:
    virtual ~material() {}

    virtual void use() {};

private:
    typedef std::vector<std::shared_ptr<shimmer::sampler>> sampler_vec;

    SHIMMER_MEMBER ( material, std::shared_ptr<shimmer::shader>, shader );

    SHIMMER_MEMBER ( material, sampler_vec, samplers );
};
}

#endif
