#ifndef SHIMMER_VIDEO_API_HPP
#define SHIMMER_VIDEO_API_HPP

#include "common/event_system.hpp"
#include "video/video.hpp"

namespace shimmer
{
class video_api : public video
{
public:
        video_api (event_system* es);
        virtual ~video_api();

        virtual video_api& source_dims(const dimensions<>& dims);
        virtual video_api& target_dims(const dimensions<>& dims);
        virtual void setup();
private:
        event_system* _es;
};
}

#endif
