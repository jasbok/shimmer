#ifndef SHIMMER_EVENT_SYSTEM_HPP
#define SHIMMER_EVENT_SYSTEM_HPP

#include "common/types.hpp"
#include "external/nano_signal_slot/nano_signal_slot.hpp"

namespace shimmer
{
class event_system
{
public:
    Nano::Signal<void (
        const dimensions<>& application,
        const dimensions<>& video ) > resolution_change;

    Nano::Signal<void ( const std::string& key ) > menu_change;
};
}

#endif

