#include "keyboard.hpp"

namespace shimmer
{
keyboard::keyboard (
    const std::shared_ptr<config>& config,
    const std::shared_ptr<event_system>& event_system )
    :_config ( config ),
     _event_system ( event_system )
{}

bool keyboard::capture()
{
    return false;
}
}
