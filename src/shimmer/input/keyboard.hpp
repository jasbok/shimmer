#ifndef SHIMMER_INPUT_KEYBOARD_HPP
#define SHIMMER_INPUT_KEYBOARD_HPP

#include "common/event_system.hpp"

namespace shimmer
{
class keyboard
{
public:
        enum class shimmer_keys
        {
                UP, DOWN, LEFT, RIGHT, SELECT, BACK, GRAB_INPUT
        };

        keyboard(class event_system* event_system);
        virtual ~keyboard();

        bool capture();
        void key_press ( shimmer_keys key );
        void key_release ( shimmer_keys key );

private:
        class event_system* _event_system;
};
}
#endif
