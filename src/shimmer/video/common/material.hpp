#ifndef SHIMMER_VIDEO_COMMON_MATERIAL_HPP
#define SHIMMER_VIDEO_COMMON_MATERIAL_HPP

#include "common/macros.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "uniform.hpp"
#include <memory>
#include <vector>

namespace shimmer
{
class material
{
public:
        material() {}
        virtual ~material() {}
private:
        typedef std::vector<std::shared_ptr<shimmer::texture>> texture_vec;
        typedef std::vector<std::shared_ptr<shimmer::uniform>> uniform_vec;

        SHIMMER_MEMBER ( material, std::shared_ptr<shimmer::shader>, shader );
        SHIMMER_MEMBER ( material, texture_vec, textures );
        SHIMMER_MEMBER ( material, uniform_vec, uniforms );
};
}

#endif
