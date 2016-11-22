#include "video.hpp"
#include "opengl_renderer.hpp"
#include <algorithm>

shimmer::video::video ( class event_system* event_system )
        : _event_system ( event_system ), _renderer ( nullptr ), _max_resolution ( 3840, 2160 )
{}

shimmer::video::~video()
{}

void shimmer::video::setup ()
{
        _calculate_aspect_ratio();
        if ( !_renderer ) {
                _renderer = std::unique_ptr<renderer> ( opengl_renderer::create() );
        }
        _renderer->source_format ( _application_resolution, _bpp, _pixel_format, _pixel_type );
        _renderer->aspect_ratio ( _aspect_ratio );
}

void shimmer::video::update ( void* pixels )
{
        _renderer->pixels ( pixels );
        render();
}

void shimmer::video::update ( void* pixels, const std::vector<rectangle<> >& rects )
{
        unsigned int xmin = _application_resolution.w;
        unsigned int ymin = _application_resolution.h;
        unsigned int xmax = 0;
        unsigned int ymax = 0;

        for ( auto r : rects ) {
                xmin = std::min<unsigned int> ( xmin, r.coords.x );
                ymin = std::min<unsigned int> ( ymin, r.coords.y );
                xmax = std::max<unsigned int> ( xmax, r.dims.w + r.coords.x );
                ymax = std::max<unsigned int> ( ymax, r.dims.h + r.coords.y );
        }

        xmin -= xmin % 2;
        xmax += xmax % 2;
        ymin -= ymin % 2;
        ymax += ymax % 2;

        _renderer->pixels ( pixels, {{xmin, ymin},{xmax - xmin, ymax - ymin}} );
        //_renderer->pixels ( pixels );
        render();
}

void shimmer::video::render()
{
        _renderer->render();
}

void shimmer::video::resize ( const dimensions<>& application, const dimensions<>& video )
{
        _application_resolution = application;

        if (
                video.w >= 128 &&
                video.w <= _max_resolution.w &&
                video.h >= 128 &&
                video.h <= _max_resolution.h ) {
                _video_resolution.w = video.w;
                _video_resolution.h = video.h;
        }
        _calculate_aspect_ratio();

        if ( _renderer ) {
                _renderer->resize ( _video_resolution );
                _renderer->aspect_ratio ( _aspect_ratio );
        }

        _event_system->resolution_change.emit ( _application_resolution, _video_resolution );
}

void shimmer::video::resize_application ( const dimensions<>& application )
{
        resize ( application, _video_resolution );
}

void shimmer::video::resize_video ( const dimensions<>& video )
{
        resize ( _application_resolution, video );
}

void * shimmer::video::map_buffer()
{
        return _renderer->map_buffer();
}

void shimmer::video::unmap_buffer()
{
        _renderer->unmap_buffer();
}

void shimmer::video::_calculate_aspect_ratio()
{
        float ar_app = _application_resolution.w / ( float ) _application_resolution.h;
        float ar_video = _video_resolution.w / ( float ) _video_resolution.h;
        float ar_factor = ar_app / ar_video;
        _aspect_ratio.w = ar_factor > 1.0f ?  1.0f : ar_factor;
        _aspect_ratio.h = ar_factor > 1.0f ? 1.0f / ar_factor : 1.0f;
}


