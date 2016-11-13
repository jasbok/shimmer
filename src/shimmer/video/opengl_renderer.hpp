#ifndef SHIMMER_VIDEO_OPENGL_RENDERER_HPP
#define SHIMMER_VIDEO_OPENGL_RENDERER_HPP

#include "opengl/quad.hpp"
#include "renderer.hpp"

namespace shimmer
{
class opengl_renderer : public renderer
{
public:
        static opengl_renderer* create();
        virtual ~opengl_renderer();
        void pixels(void * pixels) override;
        void render() override;
private:
        opengl_renderer();
        quad _quad;
};
}

#endif

