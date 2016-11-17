#ifndef SHIMMER_VIDEO_RENDERER_HPP
#define SHIMMER_VIDEO_RENDERER_HPP

#include "common/enums.hpp"
#include "common/types.hpp"

namespace shimmer
{
class renderer
{
public:
        virtual ~renderer(){};
        virtual void resize(const dimensions<>& dims) = 0;
        virtual void pixels(void* pixels) = 0;
        virtual void* pixels() = 0;
        virtual void source_format(const dimensions<>& dims, unsigned int bpp, pixel_format format, pixel_type type) = 0;
        virtual void render() = 0;
private:
};
}

#endif
