#ifndef SHIMMER_VIDEO_VIDEO_HPP
#define SHIMMER_VIDEO_VIDEO_HPP

#include "renderer.hpp"
#include "common/macros.hpp"
#include "common/types.hpp"
#include <memory>
#include <vector>

namespace shimmer
{
class video
{
public:
        enum class pixel_format
        {
                RGB, BGR, RGBA, BGRA
        };
        enum class pixel_type
        {
                UNSIGNED_BYTE, BYTE, UNSIGNED_SHORT_5_6_5, UNSIGNED_SHORT_5_6_5_REV
        };

        video();
        virtual ~video();

        virtual void setup ();
        virtual void update ();
        virtual void update ( const coordinates<>& coords, const dimensions<>& dims );
        virtual void update ( const rectangle<>& rect );
        virtual void update ( const std::vector<rectangle<>>& rects );
        virtual void* texture_surface ();

private:
        std::unique_ptr<renderer> _renderer;

        SHIMMER_MEMBER ( video, dimensions<>, source_dims);
        SHIMMER_MEMBER ( video, dimensions<>, target_dims);
        SHIMMER_MEMBER ( video, dimensions<float>, aspect_ratio );
        SHIMMER_MEMBER ( video, unsigned int, bpp );
        SHIMMER_MEMBER ( video, enum pixel_format, pixel_format );
        SHIMMER_MEMBER ( video, enum pixel_type, pixel_type );
private:
        void _calculate_aspect_ratio();
};
}

#endif
