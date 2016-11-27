#ifndef SHIMMER_VIDEO_RENDERER_HPP
#define SHIMMER_VIDEO_RENDERER_HPP

#include "common/enums.hpp"
#include "common/types.hpp"
#include <vector>

namespace shimmer
{
class renderer
{
public:
        virtual ~renderer(){};
        virtual void resize(const dimensions<>& dims) = 0;
        virtual void pixels(void* pixels) = 0;
        virtual void pixels ( void* pixels, const rectangle<coordinates<unsigned int>, dimensions<unsigned int>>& rect ) = 0;
        virtual void* map_buffer() = 0;
        virtual void unmap_buffer() = 0;
        virtual void source_format(const dimensions<>& dims, unsigned int bpp, pixel_format format, pixel_type type) = 0;
        virtual void render() = 0;

        virtual void aspect_ratio(const dimensions<float>& dims) = 0;
        virtual void texture_filter(const std::string& filter) = 0;
        virtual void foreground_shaders(const std::vector<std::string>& vertex_shaders, const std::vector<std::string>& fragment_shaders) = 0;
        virtual void background_shaders(const std::vector<std::string>& vertex_shaders, const std::vector<std::string>& fragment_shaders) = 0;
        virtual void menu_shaders(const std::vector<std::string>& vertex_shaders, const std::vector<std::string>& fragment_shaders) = 0;
        virtual void font(const std::string& regular, const std::string& bold, unsigned int size) = 0;
        virtual void font_shaders(const std::vector<std::string>& vertex_shaders, const std::vector<std::string>& fragment_shaders) = 0;
private:
};
}

#endif
