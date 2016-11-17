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

        virtual shimmer::dimensions<> resize ( const dimensions<>& dims )
        {
                auto result = window::resize ( dims );
                _es->target_dims_change.emit ( result );
                return result;
        }

private:
        event_system* _es;
};
}

#endif
