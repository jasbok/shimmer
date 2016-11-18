#ifndef SHIMMER_HPP
#define SHIMMER_HPP

#include "common/config.hpp"
#include "common/event_system.hpp"
#include "input/keyboard.hpp"
#include "input/mouse.hpp"
#include "video/video.hpp"

namespace shimmer
{
class shimmer
{
public:
        shimmer();
        virtual ~shimmer();

        class keyboard* keyboard();
        class mouse* mouse();
        class video* video();
private:
        event_system _event_system;
        class keyboard _keyboard;
        class mouse _mouse;
        class video _video;
};
}

#endif
