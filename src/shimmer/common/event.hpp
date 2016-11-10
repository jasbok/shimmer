#ifndef SHIMMER_COMMON_EVENT_H
#define SHIMMER_COMMON_EVENT_H

#include "types.hpp"

namespace shimmer
{
enum class event_type
{
        WINDOW_RESIZE,

        VIDEO_RESIZE_SOURCE,
        VIDEO_RESIZE_TARGET,

        MOUSE_MOVE,
        MOUSE_CLICK_LEFT,
        MOUSE_CLICK_RIGHT
};

enum class context_type
{
        DEFAULT,
        USER_MODE
};

class event_data
{
public:
        event_data()
                : coords ( nullptr ), dims ( nullptr )
        {}

        const coordinates<>* coords;
        const dimensions<>* dims;
};

template<typename T = event_type, typename D = event_data>
class event
{
public:
        event ( const T& type, const D& data )
                : _type ( type ), _data ( data )
        {}

        virtual ~event() {};

        const T& type() const
        {
                return _type;
        }
        const D& data() const
        {
                return _data;
        }

private:
        T _type;
        D _data;
};
}

#endif
