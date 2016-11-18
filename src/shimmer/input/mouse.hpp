#ifndef SHIMMER_INPUT_MOUSE_HPP
#define SHIMMER_INPUT_MOUSE_HPP

#include "common/event_system.hpp"
#include "common/types.hpp"

namespace shimmer
{
class mouse
{
public:
        mouse(class event_system* event_system);
        virtual ~mouse();

        template<typename T>
        void transform ( T*x, T*y )
        {
                if ( x && y ) {
                        *x = *x * _warp_factor_x;
                        *y = *y * _warp_factor_y;
                }
        }
private:
        class event_system* _event_system;
        float _warp_factor_x, _warp_factor_y;
private:
        void _calculate_warp_factors(const dimensions<>& application, const dimensions<>& video);
};
}

#endif
