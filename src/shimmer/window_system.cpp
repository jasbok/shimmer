#include "window_system.hpp"

shimmer::window_system::window_system ( event_system<>* es )
        : _es ( es )
{}

shimmer::window_system::~window_system()
{}

void shimmer::window_system::resize ( const dimensions<>& dims )
{
        event_data data;
        data.dims = &dims;
        _es->emit ( event_type::WINDOW_RESIZE, event<> ( event_type::WINDOW_RESIZE, data ) );
}
