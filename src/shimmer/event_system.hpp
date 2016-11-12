#ifndef SHIMMER_EVENT_SYSTEM_HPP
#define SHIMMER_EVENT_SYSTEM_HPP

#include "common/types.hpp"
#include "external/nano_signal_slot/nano_signal_slot.hpp"

namespace shimmer
{
class event_system
{
public:
        Nano::Signal<void(const dimensions<>& dims)> source_dims_change;
        Nano::Signal<void(const dimensions<>& dims)> target_dims_change;
private:

};
}

#endif

