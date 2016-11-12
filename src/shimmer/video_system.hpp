#ifndef SHIMMER_VIDEO_SYSTEM_HPP
#define SHIMMER_VIDEO_SYSTEM_HPP

#include "event_system.hpp"
#include "video/video.hpp"

namespace shimmer
{
class video_system : public video
{
public:
        video_system(event_system* es);
        virtual ~video_system();
private:
        event_system* _es;
};
}

#endif
