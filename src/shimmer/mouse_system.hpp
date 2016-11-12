#ifndef SHIMMER_MOUSE_SYSTEM_HPP
#define SHIMMER_MOUSE_SYSTEM_HPP

#include "event_system.hpp"
#include "input/mouse.hpp"

namespace shimmer
{
class mouse_system : public mouse
{
public:
        mouse_system ( event_system* es );
        virtual ~mouse_system();
private:
        event_system* _es;
        void _bind_events();
};
}

#endif
