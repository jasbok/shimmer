#include "shimmer.hpp"

shimmer::shimmer::shimmer()
    :_config ( std::make_shared<config>() ),
     _event_system ( std::make_shared<event_system>() ),
     _keyboard ( _config, _event_system ),
     _mouse ( _config, _event_system ),
     _video ( _config, _event_system )
{}

shimmer::shimmer::~shimmer()
{}

class shimmer::keyboard* shimmer::shimmer::keyboard()
{
    return &_keyboard;
}

class shimmer::mouse * shimmer::shimmer::mouse()
{
    return &_mouse;
}

class shimmer::video * shimmer::shimmer::video()
{
    return &_video;
}
