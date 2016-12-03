#ifndef SHIMMER_INPUT_KEYBOARD_HPP
#define SHIMMER_INPUT_KEYBOARD_HPP

#include "common/event_system.hpp"
#include "config/config.hpp"
#include <memory>

namespace shimmer
{
class keyboard
{
public:
        enum class shimmer_keys
        {
                UP, DOWN, LEFT, RIGHT, SELECT, BACK, GRAB_INPUT
        };

        keyboard(const std::shared_ptr<config>& config, const std::shared_ptr<event_system>& event_system);
        virtual ~keyboard();

        bool capture();
        void key_press ( shimmer_keys key );
        void key_release ( shimmer_keys key );

private:
        std::shared_ptr<config> _config;
        std::shared_ptr<event_system> _event_system;
};
}
#endif
