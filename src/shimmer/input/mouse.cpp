#include "mouse.hpp"

shimmer::mouse::mouse ( const std::shared_ptr<config>& config, const std::shared_ptr<event_system>& event_system )
        : _config ( config ),
          _event_system ( event_system ),
          _warp_factor_x ( 1.0f ), _warp_factor_y ( 1.0f )
{
        _event_system->resolution_change.connect<mouse, &mouse::_calculate_warp_factors> ( this );
}

shimmer::mouse::~mouse()
{}

void shimmer::mouse::_calculate_warp_factors ( const dimensions<>& application, const dimensions<>& video )
{
        if ( video.w != 0 && video.h != 0 ) {
                _warp_factor_x = application.w / ( float ) video.w;
                _warp_factor_y = application.h / ( float ) video.h;
        }
}
