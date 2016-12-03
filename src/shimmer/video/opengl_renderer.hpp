#ifndef SHIMMER_VIDEO_OPENGL_RENDERER_HPP
#define SHIMMER_VIDEO_OPENGL_RENDERER_HPP

#include "renderer.hpp"
#include "config/config.hpp"
#include "opengl/quad.hpp"
#include "opengl/render_object.hpp"
#include "opengl/shader_manager.hpp"
#include "opengl/text_renderer.hpp"
#include "opengl/texture.hpp"
#include <memory>

namespace shimmer
{
class opengl_renderer : public renderer
{
public:
        static opengl_renderer* create(const std::shared_ptr<config>& config);
        virtual ~opengl_renderer();
        void resize ( const dimensions<> & dims ) override;
        void pixels ( void * pixels ) override;
        void pixels ( void* pixels, const rectangle<coordinates<unsigned int>, dimensions<unsigned int>>& rect ) override;
        void * map_buffer() override;
        void unmap_buffer() override;
        void source_format ( const dimensions<>& dims, unsigned int bpp, pixel_format format, pixel_type type ) override;
        void render() override;

        void aspect_ratio ( const dimensions<float> & dims ) override;
        void texture_filter(const std::string& filter) override;
        void background_shaders(const std::vector<std::string> & vertex_shaders, const std::vector<std::string> & fragment_shaders) override;
        void foreground_shaders(const std::vector<std::string> & vertex_shaders, const std::vector<std::string> & fragment_shaders) override;
        void menu_shaders(const std::vector<std::string> & vertex_shaders, const std::vector<std::string> & fragment_shaders) override;
        void font(const std::string & regular, const std::string & bold, unsigned int size) override;
        void font_shaders(const std::vector<std::string> & vertex_shaders, const std::vector<std::string> & fragment_shaders) override;
private:
        std::shared_ptr<config> _config;
        std::shared_ptr<texture> _source_texture;
        shader_manager _shader_manager;
        text_renderer _text_renderer;
        dimensions<float> _aspect_ratio;
        GLenum _texture_filter;
        render_object _foreground, _background, _menu;
private:
        opengl_renderer(const std::shared_ptr<config>& config);
};
}

#endif

