#ifndef SHIMMER_WINDOW_API_HPP
#define SHIMMER_WINDOW_API_HPP

#include "common/event_system.hpp"
#include "video/window.hpp"

#include <functional>

namespace shimmer
{
class window_api : public window
{
public:
        window_api ( event_system* es );
        virtual ~window_api();

        virtual void resize ( const dimensions<>& dims )
        {
                window::resize ( dims );
                _es->target_dims_change.emit ( dims );
        }

private:
        event_system* _es;
};
}

#endif
