#ifndef SHIMMER_WINDOW_SYSTEM_HPP
#define SHIMMER_WINDOW_SYSTEM_HPP

#include "event_system.hpp"
#include "video/window.hpp"

namespace shimmer
{
class window_system : public window
{
public:
        window_system ( event_system* es );
        virtual ~window_system();
private:
        event_system* _es;
};
}

#endif
