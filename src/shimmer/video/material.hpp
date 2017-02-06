#ifndef SHIMMER_VIDEO_MATERIAL_HPP
#define SHIMMER_VIDEO_MATERIAL_HPP

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
        
private:
        SHIMMER_MEMBER ( material, std::shared_ptr<shimmer::shader>, shader);
        SHIMMER_MEMBER ( material, std::vector<std::shared_ptr<texture>>, textures );
        SHIMMER_MEMBER ( material, std::vector<std::shared_ptr<uniform>>, uniforms ); 
};
}

#endif
