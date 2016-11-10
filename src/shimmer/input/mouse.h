#ifndef SHIMMER_INPUT_MOUSE_H
#define SHIMMER_INPUT_MOUSE_H

#include "../common/types.hpp"

namespace shimmer
{
class mouse
{
public:
        template<typename T>
        void transform ( T&x, T&y )
        {
                x *= _warp_factor_x;
                y *= _warp_factor_y;
        }

protected:
        mouse();
        virtual ~mouse();

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
