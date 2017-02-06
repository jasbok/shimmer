#ifndef SHIMMER_VIDEO_MESH_HPP
#define SHIMMER_VIDEO_MESH_HPP

#include "common/macros.hpp"
#include <glm/common.hpp>
#include <vector>

namespace shimmer
{
class mesh
{
public:
private:
        SHIMMER_MEMBER(mesh, std::vector<glm::vec3[3]>, polygons);
};
}

#endif
