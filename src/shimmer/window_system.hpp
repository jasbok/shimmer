#ifndef SHIMMER_WINDOW_SYSTEM
#define SHIMMER_WINDOW_SYSTEM

#include "./video/window.hpp"
#include "event_system.hpp"

namespace shimmer
{
class window_system : window
{
public:
        window_system ( event_system<>* es );
        virtual ~window_system();
        void resize ( const dimensions<>& dims );
private:
        event_system<> *_es;
};
}

#endif
