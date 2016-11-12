#include "mouse_system.hpp"

shimmer::mouse_system::mouse_system ( event_system* es )
        : _es ( es )
{
        _es->source_dims_change.connect<mouse, &mouse_system::source>(this);
        _es->target_dims_change.connect<mouse, &mouse_system::target>(this);
}

shimmer::mouse_system::~mouse_system()
{}
