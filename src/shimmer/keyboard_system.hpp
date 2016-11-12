#ifndef SHIMMER_KEYBOARD_SYSTEM_HPP
#define SHIMMER_KEYBOARD_SYSTEM_HPP

#include "event_system.hpp"
#include "input/keyboard.hpp"

namespace shimmer
{
class keyboard_system : public keyboard
{
public:
        keyboard_system(event_system* es);
        virtual ~keyboard_system();
private:
        event_system* _es;
};
}

#endif
