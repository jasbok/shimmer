#ifndef SHIMMER_HPP
#define SHIMMER_HPP

#include "common/config.hpp"
#include "common/event_system.hpp"
#include "api/keyboard_api.hpp"
#include "api/mouse_api.hpp"
#include "api/video_api.hpp"
#include "api/window_api.hpp"

namespace shimmer
{
class shimmer
{
public:
        shimmer();
        virtual ~shimmer();

        keyboard_api* keyboard();
        mouse_api* mouse();
        video_api* video();
        window_api* window();
private:
        event_system _es;
        keyboard_api _ks;
        mouse_api _ms;
        video_api _vs;
        window_api _ws;
};
}

#endif
