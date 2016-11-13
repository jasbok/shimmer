#include "video_api.hpp"

shimmer::video_api::video_api (shimmer::event_system* es)
: _es(es)
{}

shimmer::video_api::~video_api()
{}

// void shimmer::video_api::source_dims(const dimensions<>& dims)
// {
//         video::source_dims(dims);
//         _es->source_dims_change.emit(dims);
// }
// 
// void shimmer::video_api::target_dims(const dimensions<>& dims)
// {
//         video::target_dims(dims);
//         _es->target_dims_change.emit(dims);
// }

void shimmer::video_api::setup()
{
        video::setup();
}
