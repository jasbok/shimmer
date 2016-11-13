#ifndef SHIMMER_KEYBOARD_API_HPP
#define SHIMMER_KEYBOARD_API_HPP

#include "common/event_system.hpp"
#include "input/keyboard.hpp"

namespace shimmer
{
class keyboard_api : public keyboard
{
public:
        keyboard_api (event_system* es);
        virtual ~keyboard_api();
private:
        event_system* _es;
};
}

#endif
