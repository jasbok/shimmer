#ifndef SHIMMER_INPUT_MOUSE_HPP
#define SHIMMER_INPUT_MOUSE_HPP

#include "common/config.hpp"
#include "common/event_system.hpp"
#include "common/types.hpp"
#include <memory>

namespace shimmer
{
class mouse
{
public:
        mouse ( const std::shared_ptr<config>& config, const std::shared_ptr<event_system>& event_system );
        virtual ~mouse();

        template<typename T>
        void transform ( T*x, T*y )
        {
                if ( x && y ) {
                        *x = *x * _warp_factor_x;
                        *y = *y * _warp_factor_y;
                }
        }

        template<typename T>
        void transform_inverse ( T*x, T*y )
        {
                if ( x && y ) {
                        *x = *x / _warp_factor_x;
                        *y = *y / _warp_factor_y;
                }
        }
private:
        std::shared_ptr<config> _config;
        std::shared_ptr<event_system> _event_system;
        float _warp_factor_x, _warp_factor_y;
private:
        void _calculate_warp_factors ( const dimensions<>& application, const dimensions<>& video );
};
}

#endif
