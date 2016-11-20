#ifndef SHIMMER_VIDEO_OPENGL_RENDERER_HPP
#define SHIMMER_VIDEO_OPENGL_RENDERER_HPP

#include "renderer.hpp"
#include "opengl/quad.hpp"
#include "opengl/render_object.hpp"
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
        void resize ( const dimensions<> & dims ) override;
        void pixels ( void * pixels ) override;
        void * map_buffer() override;
        void unmap_buffer() override;
        void source_format ( const dimensions<>& dims, unsigned int bpp, pixel_format format, pixel_type type ) override;
        void aspect_ratio ( const dimensions<float> & dims ) override;
        void render() override;

private:
        SHIMMER_GETTER ( opengl_renderer, dimensions<float>, aspect_ratio );
        render_object _foreground, _background;
        shader_manager _shader_manager;
        std::shared_ptr<texture> _source_texture;
private:
        opengl_renderer();
};
}

#endif

