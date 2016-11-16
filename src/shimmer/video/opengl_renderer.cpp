#include "opengl_renderer.hpp"
#include "common/config.hpp"
#include <GL/glew.h>

shimmer::opengl_renderer * shimmer::opengl_renderer::create()
{
        glewExperimental = true;
        glewInit();
        return new opengl_renderer();
}

shimmer::opengl_renderer::opengl_renderer()
{
        _foreground_shader = std::shared_ptr<shader> ( _shader_manager.create (
        {config::instance().vertex_shader}, {config::instance().fragment_shader} ) );
        _foreground.bind ( _foreground_shader );
}

shimmer::opengl_renderer::~opengl_renderer()
{}

void shimmer::opengl_renderer::source_format ( const dimensions<>& dims, unsigned int bpp, shimmer::pixel_format format, shimmer::pixel_type type )
{
        GLenum pixel_format = GL_BGRA;
        GLenum pixel_type = GL_UNSIGNED_BYTE;
        switch ( format ) {
        case pixel_format::RGB:
                pixel_format = GL_RGB;
                break;
        case pixel_format::BGR:
                pixel_format = GL_BGR;
                break;
        case pixel_format::BGRA:
                pixel_format = GL_BGRA;
                break;
        default:
                break;
        }

        switch ( type ) {
        case pixel_type::UNSIGNED_SHORT_5_6_5:
                pixel_type = GL_UNSIGNED_SHORT_5_6_5;
                break;
        case pixel_type::UNSIGNED_BYTE:
                pixel_type = GL_UNSIGNED_BYTE;
                break;
        default:
                break;
        }

        _source_texture
        .dims ( { static_cast<GLint> ( dims.w ), static_cast<GLint> ( dims.h ) } )
        .bpp ( bpp )
        .pixel_format ( pixel_format )
        .pixel_type ( pixel_type )
        .filter ( GL_NEAREST )
        .texunit(GL_TEXTURE0)
        .location(_foreground_shader->uniforms("texture_unit").location())
        .setup();
}

void shimmer::opengl_renderer::render()
{
        glClearColor ( 1.0f, 0.0f, 0.0f, 1.0f );
        glClear ( GL_COLOR_BUFFER_BIT );
        _source_texture.bind();
        _foreground.render();
}

void shimmer::opengl_renderer::pixels ( void* pixels )
{}

