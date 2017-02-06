#ifndef SHIMMER_VIDEO_OBJECT_HPP
#define SHIMMER_VIDEO_OBJECT_HPP

#include "common/macros.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include <glm/glm.hpp>
#include <memory>

namespace shimmer
{
class object
{
public:

private:
        SHIMMER_MEMBER(object, glm::mat4, transform);
        SHIMMER_MEMBER(object, std::vector<std::shared_ptr<shimmer::object>>, children);
        SHIMMER_MEMBER(object, std::shared_ptr<shimmer::material>, material);
        SHIMMER_MEMBER(object, std::shared_ptr<shimmer::mesh>, mesh);
};
}

#endif
