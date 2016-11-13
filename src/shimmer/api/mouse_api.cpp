#include "mouse_api.hpp"

shimmer::mouse_api::mouse_api ( event_system* es )
        : _es ( es )
{
        _es->source_dims_change.connect<mouse, &mouse_api::source>(this);
        _es->target_dims_change.connect<mouse, &mouse_api::target>(this);
}

shimmer::mouse_api::~mouse_api()
{}
