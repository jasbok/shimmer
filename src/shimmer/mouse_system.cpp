#include "mouse_system.hpp"

shimmer::mouse_system::mouse_system ( event_system<>* es )
        : _es ( es )
{
        _bind_events();
}

shimmer::mouse_system::~mouse_system()
{}

void shimmer::mouse_system::_bind_events()
{
        _es->bind ( event_type::VIDEO_RESIZE_SOURCE, [this] ( const event<>& e ) {
                source ( *e.data().dims );
        } );
        _es->bind ( event_type::VIDEO_RESIZE_TARGET, [this] ( const event<>& e ) {
                target ( *e.data().dims );
        } );
}
