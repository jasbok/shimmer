#include "mouse.hpp"

shimmer::mouse::mouse()
        : _warp_factor_x ( 1.0f ), _warp_factor_y ( 1.0f )
{}

shimmer::mouse::~mouse()
{}

void shimmer::mouse::source ( const dimensions<>& dims )
{
        _source_dims = dims;
        _calculate_warp_factors();
}

void shimmer::mouse::target ( const dimensions<>& dims )
{
        _target_dims = dims;
        _calculate_warp_factors();
}

void shimmer::mouse::_calculate_warp_factors()
{
        if ( _source_dims.w != 0 && _source_dims.h != 0 ) {
                _warp_factor_x = _target_dims.w / ( float ) _source_dims.w;
                _warp_factor_y = _target_dims.h / ( float ) _source_dims.h;
        }
}
