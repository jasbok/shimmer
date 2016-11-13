#ifndef SHIMMER_MOUSE_API_HPP
#define SHIMMER_MOUSE_API_HPP

#include "common/event_system.hpp"
#include "input/mouse.hpp"

namespace shimmer
{
class mouse_api : public mouse
{
public:
        mouse_api ( event_system* es );
        virtual ~mouse_api();
private:
        event_system* _es;
};
}

#endif
