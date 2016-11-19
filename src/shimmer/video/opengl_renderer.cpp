#include "opengl_renderer.hpp"
#include "opengl/formats.hpp"
#include "opengl/quad.hpp"
#include "common/config.hpp"
#include <GL/glew.h>

shimmer::opengl_renderer * shimmer::opengl_renderer::create()
{
        glewExperimental = true;
        glewInit();
        return new opengl_renderer();
}

shimmer::opengl_renderer::opengl_renderer()
        : _aspect_ratio ( {1.0, 1.0} )
{
        //_foreground.model ( std::make_shared<quad> ( _aspect_ratio ) );
        //_foreground.shader ( std::make_shared<shader> ( _shader_manager.create ({config::instance().vertex_shader}, {config::instance().fragment_shader} ) ) );
        //_foreground.texture ( std::make_shared<texture> () );

        _source_texture = std::make_shared<texture>();
        _shader_manager.application_texture ( _source_texture );

        _foreground = quad ( _aspect_ratio );
        _foreground_shader = std::shared_ptr<shader> ( _shader_manager.create ( {config::instance().vertex_shader}, {config::instance().fragment_shader} ) );
        _foreground.bind ( _foreground_shader );
}

shimmer::opengl_renderer::~opengl_renderer()
{}

void shimmer::opengl_renderer::resize ( const dimensions<>& dims )
{
        glViewport ( 0, 0, dims.w, dims.h );
}

void shimmer::opengl_renderer::source_format ( const dimensions<>& dims, unsigned int bpp, shimmer::pixel_format format, shimmer::pixel_type type )
{
        _source_texture
        ->dims ( { static_cast<GLint> ( dims.w ), static_cast<GLint> ( dims.h ) } )
        .bpp ( bpp )
        .pixel_format ( gl_formats::pixel_format_from ( format ) )
        .pixel_type ( gl_formats::pixel_type_from ( type ) )
        .filter ( GL_NEAREST )
        .setup();
}

void shimmer::opengl_renderer::render()
{
        glClearColor ( 1.0f, 0.0f, 0.0f, 1.0f );
        glClear ( GL_COLOR_BUFFER_BIT );

        _secondary.render();
        _main.render();
        _menu.render();

        _foreground_shader->use_program();
        _foreground.render();
}

void shimmer::opengl_renderer::pixels ( void* pixels )
{
        _source_texture->pixels ( pixels );
}

void * shimmer::opengl_renderer::pixels()
{
        return nullptr;
}
