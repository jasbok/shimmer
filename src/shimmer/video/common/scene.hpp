#ifndef SHIMMER_VIDEO_COMMON_SCENE_HPP
#define SHIMMER_VIDEO_COMMON_SCENE_HPP

#include "common/macros.hpp"
#include "fbo.hpp"
#include "model.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace shimmer
{
class scene
{
public:
    scene() {}

    virtual ~scene() {}

private:
    typedef std::vector<std::shared_ptr<shimmer::model>> model_vec;

    SHIMMER_MEMBER ( scene, std::string, id );

    SHIMMER_MEMBER ( scene, glm::mat4, camera );

    SHIMMER_MEMBER ( scene, model_vec, models );

    SHIMMER_MEMBER ( scene, shimmer::fbo, fbo );
};
}

#endif
