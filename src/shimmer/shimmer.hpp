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

        keyboard* keyboard_api();
        mouse* mouse_api();
        video* video_api();
        window* window_api();
private:
        event_system _es;
        keyboard_system _ks;
        mouse_system _ms;
        video_system _vs;
        window_system _ws;
};
}

#endif
