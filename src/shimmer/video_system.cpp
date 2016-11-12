#include "video_system.hpp"

shimmer::video_system::video_system(shimmer::event_system* es)
: _es(es)
{}

shimmer::video_system::~video_system()
{}

void shimmer::video_system::source(const dimensions<>& dims)
{
        video::source(dims);
        _es->source_dims_change.emit(dims);
}

void shimmer::video_system::target(const dimensions<>& dims)
{
        video::target(dims);
        _es->target_dims_change.emit(dims);
}
