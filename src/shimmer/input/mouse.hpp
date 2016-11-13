#ifndef SHIMMER_INPUT_MOUSE_HPP
#define SHIMMER_INPUT_MOUSE_HPP

#include "../common/types.hpp"

namespace shimmer
{
class mouse
{
public:
        mouse();
        virtual ~mouse();

        template<typename T>
        void transform ( T*x, T*y )
        {
                if ( x && y ) {
                        *x = *x * _warp_factor_x;
                        *y = *y * _warp_factor_y;
                }
        }

        void source ( const dimensions<>& dims );
        void target ( const dimensions<>& dims );
private:
        dimensions<> _source_dims, _target_dims;
        float _warp_factor_x, _warp_factor_y;

private:
        void _calculate_warp_factors();
};
}

#endif
