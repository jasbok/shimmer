#ifndef SHIMMER_VIDEO_VIDEO_HPP
#define SHIMMER_VIDEO_VIDEO_HPP

#include "renderer.hpp"
#include "common/enums.hpp"
#include "common/event_system.hpp"
#include "common/macros.hpp"
#include "common/types.hpp"
#include <memory>
#include <vector>

namespace shimmer
{
class video
{
public:
        video(class event_system* event_system);
        virtual ~video();

        void setup ();
        void update ( void* pixels );
        void update ( void* pixels, const std::vector<rectangle<>>& rects );
        void render();
        void* map_buffer();
        void unmap_buffer();

        void resize ( const dimensions<>& application, const dimensions<>& video );
        void resize_application ( const dimensions<>& application );
        void resize_video ( const dimensions<>& video );
private:
        class event_system* _event_system;
        std::unique_ptr<renderer> _renderer;
        SHIMMER_GETTER ( video, dimensions<>, application_resolution );
        SHIMMER_GETTER ( video, dimensions<>, video_resolution );
        SHIMMER_MEMBER ( video, dimensions<>, max_resolution );
        SHIMMER_MEMBER ( video, dimensions<float>, aspect_ratio );
        SHIMMER_MEMBER ( video, unsigned int, bpp );
        SHIMMER_MEMBER ( video, enum pixel_format, pixel_format );
        SHIMMER_MEMBER ( video, enum pixel_type, pixel_type );

private:
        void _calculate_aspect_ratio();
};
}

#endif
