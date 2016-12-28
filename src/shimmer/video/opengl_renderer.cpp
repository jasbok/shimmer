#include "opengl_renderer.hpp"
#include "font/font_loader.hpp"
#include "opengl/formats.hpp"
#include "opengl/quad.hpp"
#include <GL/glew.h>

shimmer::opengl_renderer * shimmer::opengl_renderer::create ( const std::shared_ptr<config>& config )
{
        glewExperimental = true;
        glewInit();
        glEnable ( GL_BLEND );
        glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
        return new opengl_renderer ( config );
}

shimmer::opengl_renderer::opengl_renderer ( const std::shared_ptr<config>& config )
        : _config ( config ),
          _source_texture ( std::make_shared<texture>() ),
          _fbo_texture ( std::make_shared<texture>() ),
          _shader_manager()
{
        _fbo_texture->internal_format(GL_RGBA).bpp(32).pixel_format(GL_RGBA).pixel_type(GL_UNSIGNED_BYTE).filter(GL_LINEAR);
        glGenFramebuffersEXT ( 1, &_fbo );
        glBindFramebufferEXT ( GL_FRAMEBUFFER_EXT, _fbo );
        glFramebufferTexture2DEXT ( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, _fbo_texture->gl_texture(), 0 );
        glBindFramebufferEXT ( GL_FRAMEBUFFER_EXT, 0 );

        _foreground = render_object (
                              std::make_shared<quad> ( _aspect_ratio, true),
                              _shader_manager.create ( {"/usr/local/libshimmer/shaders/surface/vs/default.vert"}, {"/usr/local/libshimmer/shaders/surface/fs/default.frag"} )
                      );

        _shader_manager.application_texture ( _source_texture );

        glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
}

shimmer::opengl_renderer::~opengl_renderer()
{
        glDeleteFramebuffersEXT ( 1, &_fbo );
}

void shimmer::opengl_renderer::resize ( const dimensions<>& dims )
{
        _viewport_resolution = dims;
        _text_renderer.resolution ( dimensions<GLfloat> ( dims.w, dims.h ) );

        dimensions<> fbo_dims = _source_texture->dims();
        dimensions<> scale_factor = {dims.w / fbo_dims.w, dims.h / fbo_dims.h};
        scale_factor.w -= scale_factor.w % 2; scale_factor.w = scale_factor.w > 0 ? scale_factor.w : 1;
        scale_factor.h -= scale_factor.h % 2; scale_factor.h = scale_factor.h > 0 ? scale_factor.h : 1;

        if(fbo_dims.w < dims.w) fbo_dims.w *= scale_factor.w;
        if(fbo_dims.h < dims.h) fbo_dims.h *= scale_factor.h;

        _fbo_texture->dims ( fbo_dims ).setup();
}

void shimmer::opengl_renderer::source_format ( const dimensions<>& dims, unsigned int bpp, shimmer::pixel_format format, shimmer::pixel_type type )
{
        _source_texture
        ->dims ( { static_cast<GLuint> ( dims.w ), static_cast<GLuint> ( dims.h ) } )
        .bpp ( bpp )
        .pixel_format ( gl_formats::pixel_format_from ( format ) )
        .pixel_type ( gl_formats::pixel_type_from ( type ) )
        .setup();
}

void shimmer::opengl_renderer::render()
{
        glBindFramebufferEXT ( GL_FRAMEBUFFER_EXT, _fbo );
        glViewport ( 0, 0, _fbo_texture->dims().w, _fbo_texture->dims().h );
        //glClearColor ( 0.0f, 1.0f, 0.0f, 1.0f );
        //glClear ( GL_COLOR_BUFFER_BIT );
        _foreground_fbo.render();
        glBindFramebufferEXT ( GL_FRAMEBUFFER_EXT, 0 );

        glViewport ( 0, 0, _viewport_resolution.w, _viewport_resolution.h );
        //glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
        glClear ( GL_COLOR_BUFFER_BIT );
        //_background.render();

        glActiveTexture ( GL_TEXTURE0 );
        glBindTexture ( GL_TEXTURE_2D, _fbo_texture->gl_texture() );
        //glBindTexture ( GL_TEXTURE_2D, _source_texture->gl_texture() );
        _foreground.render();
        //_menu.render();
        //_text_renderer.draw ( "// Fragment_Shader -> hsv_adaptive_scaler.frag", {20,20} );
}

void shimmer::opengl_renderer::aspect_ratio ( const dimensions<float>& dims )
{
        _aspect_ratio = dims;
        std::static_pointer_cast<quad> ( _foreground.render_model() )->aspect_ratio ( _aspect_ratio, true);
}

void shimmer::opengl_renderer::texture_filter ( const std::string& filter )
{
        _texture_filter = filter.compare ( "linear" ) == 0 ? GL_LINEAR : GL_NEAREST;
        _source_texture->filter ( _texture_filter );
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

void shimmer::opengl_renderer::background_shaders ( const std::vector<std::string>& vertex_shaders, const std::vector<std::string>& fragment_shaders )
{
        _background = render_object (
                              std::make_shared<quad> ( dimensions<float> ( 1.0f, 1.0f ) ),
                              _shader_manager.create ( vertex_shaders, fragment_shaders )
                      );
}

void shimmer::opengl_renderer::foreground_shaders ( const std::vector<std::string>& vertex_shaders, const std::vector<std::string>& fragment_shaders )
{
        _foreground_fbo = render_object (
                                  std::make_shared<quad> (),
                                  _shader_manager.create ( vertex_shaders, fragment_shaders )
                          );
}

void shimmer::opengl_renderer::menu_shaders ( const std::vector<std::string>& vertex_shaders, const std::vector<std::string>& fragment_shaders )
{
        _menu = render_object (
                        std::make_shared<quad> ( dimensions<float> ( 1.0f, 1.0f ) ),
                        _shader_manager.create ( vertex_shaders, fragment_shaders )
                );
        _menu.render_shader()->set_uniform ( "colour", glm::vec4 ( 0.0f, 0.0f, 0.0f, 0.75f ) );
}

void shimmer::opengl_renderer::font ( const std::string& regular, const std::string& bold, unsigned int size )
{
        font_loader font_loader;
        std::shared_ptr<font_face> face = font_loader.load ( regular, size );
        std::shared_ptr<gl_font> gl_font = std::make_shared<class gl_font>();
        gl_font->font_face ( *face );
        _text_renderer.font ( gl_font );
}

void shimmer::opengl_renderer::font_shaders ( const std::vector<std::string>& vertex_shaders, const std::vector<std::string>& fragment_shaders )
{
        _text_renderer.shader ( _shader_manager.create ( vertex_shaders, fragment_shaders ) );
}
