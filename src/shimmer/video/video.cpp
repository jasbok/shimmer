#include "video.hpp"
#include "opengl_renderer.hpp"

shimmer::video::video()
        : _renderer ( nullptr )
{}

shimmer::video::~video()
{}

void shimmer::video::setup ()
{
        _calculate_aspect_ratio();
        if ( !_renderer ) {
                _renderer = std::unique_ptr<renderer>(opengl_renderer::create());
        }
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

void * shimmer::video::texture_surface()
{
        return nullptr;
}

void shimmer::video::_calculate_aspect_ratio()
{
        float ar_source = _source_dims.w / ( float ) _source_dims.h;
        float ar_target = _target_dims.w / ( float ) _target_dims.h;
        float ar_factor = ar_source / ar_target;
        _aspect_ratio.w = ar_factor > 1.0f ?  1.0f : ar_factor;
        _aspect_ratio.h = ar_factor > 1.0f ? 1.0f / ar_factor : 1.0f;
}
