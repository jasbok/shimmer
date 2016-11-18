#include "keyboard.hpp"

shimmer::keyboard::keyboard(class event_system* event_system)
: _event_system(event_system)
{}

shimmer::keyboard::~keyboard()
{}

bool shimmer::keyboard::capture()
{
        return false;
}
