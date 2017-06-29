#ifndef SHIMMER_VIDEO_COMMON_MESH_HPP
#define SHIMMER_VIDEO_COMMON_MESH_HPP

#include "common/macros.hpp"
#include <glm/common.hpp>
#include <string>
#include <vector>

namespace shimmer
{
class mesh
{
public:
        mesh();
        mesh(const std::string& id);
        virtual ~mesh();
private:
        SHIMMER_MEMBER ( mesh, std::string, id );
        SHIMMER_MEMBER ( mesh, std::vector<std::vector<glm::vec3>>, polygons );
};
}

#endif
