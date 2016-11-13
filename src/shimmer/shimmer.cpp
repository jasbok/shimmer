#include "shimmer.hpp"

shimmer::shimmer::shimmer()
        : _es(), _ks ( &_es ), _ms ( &_es ), _vs ( &_es ), _ws ( &_es )
{}

shimmer::shimmer::~shimmer()
{}

shimmer::keyboard_api * shimmer::shimmer::keyboard()
{
        return &_ks;
}

shimmer::mouse_api * shimmer::shimmer::mouse()
{
        return &_ms;
}

shimmer::video_api * shimmer::shimmer::video()
{
        return &_vs;
}

shimmer::window_api * shimmer::shimmer::window()
{
        return &_ws;
}
