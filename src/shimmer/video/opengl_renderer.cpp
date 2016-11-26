#include "opengl_renderer.hpp"
#include "font/font_loader.hpp"
#include "opengl/formats.hpp"
#include "opengl/quad.hpp"
#include "common/config.hpp"
#include <GL/glew.h>

shimmer::opengl_renderer * shimmer::opengl_renderer::create()
{
        glewExperimental = true;
        glewInit();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
        return new opengl_renderer();
}

shimmer::opengl_renderer::opengl_renderer()
        : _aspect_ratio ( {1.0f, 1.0f} )
{
        _source_texture = std::make_shared<texture>();
        _shader_manager.application_texture ( _source_texture );

        _foreground = render_object (
                              std::make_shared<quad> ( _aspect_ratio ),
                              _shader_manager.create (
        { config::instance().shaders_prefix + "/surface/vs/" + config::instance().vertex_shader},
        { config::instance().shaders_prefix + "/surface/fs/hsv_adaptive_scaler.frag"} ) );

        _background = render_object (
                              std::make_shared<quad> ( dimensions<float> ( 1.0f, 1.0f ) ),
                              _shader_manager.create (
        { config::instance().shaders_prefix + "/surface/vs/" + config::instance().vertex_shader},
        { config::instance().shaders_prefix + "/surface/fs/hsv.frag"} ) );

        font_loader font_loader;
        std::shared_ptr<font_face> face = font_loader.load ( "../../../fonts/xolonium/ttf/Xolonium-Regular.ttf", 48 );
        std::shared_ptr<gl_font> gl_font = std::make_shared<class gl_font>();
        gl_font->font_face(*face);

        auto text_shader = _shader_manager.create (
        { config::instance().shaders_prefix + "/text/text.vert"},
        { config::instance().shaders_prefix + "/text/text.frag"} );

        _text_renderer.font(gl_font);
        _text_renderer.shader(text_shader);
}

shimmer::opengl_renderer::~opengl_renderer()
{}

void shimmer::opengl_renderer::resize ( const dimensions<>& dims )
{
        glViewport ( 0, 0, dims.w, dims.h );
        _text_renderer.resolution(dimensions<GLfloat>(dims.w, dims.h));
}

void shimmer::opengl_renderer::source_format ( const dimensions<>& dims, unsigned int bpp, shimmer::pixel_format format, shimmer::pixel_type type )
{
        _source_texture
        ->dims ( { static_cast<GLuint> ( dims.w ), static_cast<GLuint> ( dims.h ) } )
        .bpp ( bpp )
        .pixel_format ( gl_formats::pixel_format_from ( format ) )
        .pixel_type ( gl_formats::pixel_type_from ( type ) )
        .filter ( GL_LINEAR )
        .setup();
}

void shimmer::opengl_renderer::render()
{
        glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
        glClear ( GL_COLOR_BUFFER_BIT );
        _background.render();
        _foreground.render();
        //_text_renderer.draw("// Fragment_Shader -> hsv_adaptive_scaler.frag", {50,50});
}

void shimmer::opengl_renderer::aspect_ratio ( const dimensions<float>& dims )
{
        _aspect_ratio = dims;
        std::static_pointer_cast<quad> ( _foreground.render_model() )->aspect_ratio ( _aspect_ratio );
}

void shimmer::opengl_renderer::pixels ( void* pixels )
{
        _source_texture->pixels ( pixels );
}

void shimmer::opengl_renderer::pixels ( void* pixels, const rectangle<coordinates<unsigned int>, dimensions<unsigned int> >& rect )
{
        _source_texture->pixels ( pixels, rect );
}

void * shimmer::opengl_renderer::map_buffer()
{
        return _source_texture->map_buffer();
}

void shimmer::opengl_renderer::unmap_buffer()
{
        _source_texture->unmap_buffer();
}
