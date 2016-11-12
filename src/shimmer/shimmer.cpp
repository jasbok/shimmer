#include "shimmer.hpp"

shimmer::shimmer::shimmer()
        : _es(), _ks ( &_es ), _ms ( &_es ), _vs ( &_es ), _ws ( &_es )
{}

shimmer::shimmer::~shimmer()
{}

shimmer::keyboard_system * shimmer::shimmer::keyboard_api()
{
        return &_ks;
}

shimmer::mouse_system * shimmer::shimmer::mouse_api()
{
        return &_ms;
}

shimmer::video_system * shimmer::shimmer::video_api()
{
        return &_vs;
}

shimmer::window_system * shimmer::shimmer::window_api()
{
        return &_ws;
}
