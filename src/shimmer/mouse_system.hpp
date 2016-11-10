#ifndef MOUSE_SYSTEM_H
#define MOUSE_SYSTEM_H

#include "./input/mouse.h"
#include "./event_system.hpp"

namespace shimmer
{
class mouse_system : public mouse
{
public:
        mouse_system ( event_system<>* es );
        virtual ~mouse_system();
private:
        event_system<>* _es;
        void _bind_events();
};
}

#endif
