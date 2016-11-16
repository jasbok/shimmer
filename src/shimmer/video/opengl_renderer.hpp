#ifndef SHIMMER_VIDEO_OPENGL_RENDERER_HPP
#define SHIMMER_VIDEO_OPENGL_RENDERER_HPP

#include "renderer.hpp"
#include "opengl/quad.hpp"
#include "opengl/shader_manager.hpp"
#include "opengl/texture.hpp"
#include <memory>

namespace shimmer
{
class opengl_renderer : public renderer
{
public:
        static opengl_renderer* create();
        virtual ~opengl_renderer();
        void pixels(void * pixels) override;
        void source_format(const dimensions<>& dims, unsigned int bpp, pixel_format format, pixel_type type) override;
        void render() override;
private:
        quad _foreground, _background;
        std::shared_ptr<shader> _foreground_shader, _background_shader;
        shader_manager _shader_manager;
        texture _source_texture;
private:
        opengl_renderer();
};
}

#endif

