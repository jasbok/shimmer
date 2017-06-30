#ifndef SHIMMER_VIDEO_COMMON_MODEL_HPP
#define SHIMMER_VIDEO_COMMON_MODEL_HPP

#include "common/macros.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include <glm/glm.hpp>
#include <memory>

namespace shimmer
{
class model
{
public:
    model() {}

    virtual ~model() {}

private:
    typedef std::vector<std::shared_ptr<shimmer::model>> model_vec;

    SHIMMER_MEMBER ( model, model_vec, children );

    SHIMMER_MEMBER ( model, std::shared_ptr<shimmer::material>, material );

    SHIMMER_MEMBER ( model, std::shared_ptr<shimmer::mesh>, mesh );

    SHIMMER_MEMBER ( model, glm::mat4, transform );

    SHIMMER_MEMBER ( model, bool, visible );
};
}

#endif
