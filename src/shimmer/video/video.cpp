#include "video.hpp"
#include "opengl_renderer.hpp"

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
        _renderer->aspect_ratio(_aspect_ratio);
}

void shimmer::video::update()
{
        _renderer->render();
}

void shimmer::video::update ( const coordinates<>& coords, const dimensions<>& dims )
{
        _renderer->render();
}

void shimmer::video::update ( const rectangle<>& rect )
{
        _renderer->render();
}

void shimmer::video::update ( const std::vector<rectangle<> >& rects )
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
                _renderer->aspect_ratio( _aspect_ratio );
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

void shimmer::video::pixels ( void* pixels )
{
        _renderer->pixels ( pixels );
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

