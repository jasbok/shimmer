#include "keyboard.hpp"

shimmer::keyboard::keyboard ( const std::shared_ptr<config>& config, const std::shared_ptr<event_system>& event_system )
        :_config ( config ),
         _event_system ( event_system )
{}

shimmer::keyboard::~keyboard()
{}

bool shimmer::keyboard::capture()
{
        return false;
}
