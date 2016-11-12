#include "window_system.hpp"

shimmer::window_system::window_system ( event_system* es )
        : _es ( es )
{}

shimmer::window_system::~window_system()
{}

void shimmer::window_system::resize(const dimensions<>& dims)
{
        window::dims(dims);
        _es->target_dims_change.emit(dims);
}
