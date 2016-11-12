#ifndef SHIMMER_HPP
#define SHIMMER_HPP

#include "config.hpp"
#include "event_system.hpp"
#include "keyboard_system.hpp"
#include "mouse_system.hpp"
#include "video_system.hpp"
#include "window_system.hpp"

namespace shimmer
{
class shimmer
{
public:
        shimmer();
        virtual ~shimmer();

        keyboard_system* keyboard_api();
        mouse_system* mouse_api();
        video_system* video_api();
        window_system* window_api();
private:
        event_system _es;
        keyboard_system _ks;
        mouse_system _ms;
        video_system _vs;
        window_system _ws;
};
}

#endif
