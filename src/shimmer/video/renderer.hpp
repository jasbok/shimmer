#ifndef SHIMMER_VIDEO_RENDERER_HPP
#define SHIMMER_VIDEO_RENDERER_HPP

#include "common/enums.hpp"
#include "common/types.hpp"
#include "video/common/scene.hpp"
#include <vector>

namespace shimmer
{
class renderer
{
public:
        virtual ~renderer() {};
        void render(std::shared_ptr<scene> scene);

private:
};
}

#endif
