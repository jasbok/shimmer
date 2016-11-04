#include "hw_surface.h"

#include "sdl_shim.h"
#include "opengl_helpers.h"
#include <SDL/SDL_image.h>

#include <stdlib.h>

namespace shimmer
{
hw_surface::hw_surface ( SDL_Surface* source, SDL_Surface* target )
        : _source ( source ), _target ( target ), _pbo_count ( 3 ), _pbo_index ( 0 ),
          _texture_filter ( GL_NEAREST ), _keep_aspect_ratio ( true ), _palette ( nullptr ),
          _update_ticks ( 0 )
{

        _pbo = new GLuint[_pbo_count];

        glGenBuffers ( 1, &_vbo );
        glGenBuffers ( _pbo_count, _pbo );
        glGenTextures ( 1, &_texture );
        glGenVertexArrays ( 1, &_vao );
        _shader_program = glCreateProgram();

        _init();
}

hw_surface::~hw_surface()
{
        glDeleteBuffers ( 1, &_vbo );
        glDeleteBuffers ( _pbo_count, _pbo );
        glDeleteTextures ( 1, &_texture );
        glDeleteVertexArrays ( 1, &_vao );
        glDeleteProgram ( _shader_program );

        delete _pbo;

        if ( _palette ) {
                delete [] _palette;
        }
}

SDL_Surface * hw_surface::source()
{
        return _source;
}

void hw_surface::source ( SDL_Surface* source )
{
        _source = source;
}

SDL_Surface * hw_surface::target()
{
        return _target;
}

void hw_surface::target ( SDL_Surface* target )
{
        _target = target;
}

void hw_surface::update()
{
        _copy_source_to_texture();
        _draw_quad();
}

void hw_surface::update ( int numrects, SDL_Rect* rects )
{
        _copy_source_to_texture ( numrects, rects );
        _draw_quad();
}

void hw_surface::refresh()
{
        _draw_quad();
}

void hw_surface::resize()
{
        glBindFramebuffer ( GL_FRAMEBUFFER, 0 );
        _setup_buffers();
        glViewport ( 0,0,_target->w,_target->h );
        update();
}

void hw_surface::set_config ( config config )
{
        switch ( config.filter_level ) {
        case 0:
                _texture_filter = GL_NEAREST;
                break;
        case 1:
                _texture_filter = GL_LINEAR;
                break;
        default:
                _texture_filter = GL_NEAREST;
                break;
        }
        _keep_aspect_ratio = config.keep_aspect_ratio;

        _setup_buffers();
        _setup_textures();
        update();
}

void hw_surface::_init()
{
        switch ( _source->format->BitsPerPixel ) {
        case 8:
                _pixel_format = GL_BGRA;
                _pixel_type = GL_UNSIGNED_BYTE;
                _create_palette();
                break;
        case 16:
                _pixel_format = GL_RGB;
                _pixel_type = GL_UNSIGNED_SHORT_5_6_5;
                break;
        case 32:
                _pixel_format = GL_BGRA;
                _pixel_type = GL_UNSIGNED_BYTE;
                break;
        default:
                break;
        }

        _gl_init();
}


void hw_surface::_gl_init()
{
        glPixelStorei ( GL_UNPACK_ALIGNMENT, 4 );

        _setup_buffers();
        _setup_textures();
        _setup_program();
        _setup_vao();
}

void hw_surface::_draw_quad()
{
        auto now = sdl::SDL_GetTicks();
        if ( ( now - _update_ticks ) > ( 1000/60 ) ) {
                glBindVertexArray ( _vao );
                glBindTexture ( GL_TEXTURE_2D, _texture );
                glUseProgram ( _shader_program );
                glUniform1i ( _texunit_uniform, 0 );
                glUniform2f ( _ratio_uniform, _ratio_w, _ratio_h );

                glClearColor ( 0.0, 0.0, 0.0, 0.0 );
                glClear ( GL_COLOR_BUFFER_BIT );
                glDrawArrays ( GL_QUADS, 0, 4 );

                glUseProgram ( 0 );
                glBindVertexArray ( 0 );
                sdl::SDL_GL_SwapBuffers();
                _update_ticks = sdl::SDL_GetTicks();
        }
}

void hw_surface::_setup_buffers()
{
        GLfloat aspect_ratio_x = 1.0f;
        GLfloat aspect_ratio_y = 1.0f;

        if ( _keep_aspect_ratio ) {
                GLfloat ar_source = _source->w / ( float ) _source->h;
                GLfloat ar_target = _target->w / ( float ) _target->h;
                GLfloat ar_factor = ar_source / ar_target;
                aspect_ratio_x = ar_factor > 1.0f ?  1.0f : ar_factor;
                aspect_ratio_y = ar_factor > 1.0f ? 1.0f / ar_factor : 1.0f;
        }

        GLfloat screen_vertices[] = {
                // Vertices               // Texcoord
                aspect_ratio_x,   aspect_ratio_y,   0.0,        1.0, 0.0,
                aspect_ratio_x,   -aspect_ratio_y,  0.0,        1.0, 1.0,
                -aspect_ratio_x,  -aspect_ratio_y,  0.0,        0.0, 1.0,
                -aspect_ratio_x,  aspect_ratio_y,   0.0,        0.0, 0.0
        };

        _ratio_w = _target->w * aspect_ratio_x / (float) _source->w;
        _ratio_h = _target->h * aspect_ratio_y / (float) _source->h;

        glBindBuffer ( GL_ARRAY_BUFFER, _vbo );
        glBufferData ( GL_ARRAY_BUFFER, sizeof ( screen_vertices ), screen_vertices, GL_STATIC_DRAW );
        glBindBuffer ( GL_ARRAY_BUFFER, 0 );

        for ( int i = 0; i < _pbo_count; i++ ) {
                glBindBuffer ( GL_PIXEL_UNPACK_BUFFER, _pbo[i] );
                glBufferData ( GL_PIXEL_UNPACK_BUFFER, _source->w * _source->h * _source->format->BytesPerPixel, 0, GL_STREAM_DRAW );
                glBindBuffer ( GL_PIXEL_UNPACK_BUFFER, 0 );
        }
}

void hw_surface::_setup_textures()
{
        glBindTexture ( GL_TEXTURE_2D, _texture );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _texture_filter );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _texture_filter );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexImage2D ( GL_TEXTURE_2D,
                       0,
                       GL_RGB,
                       _source->w,
                       _source->h,
                       0,
                       _pixel_format,
                       _pixel_type,
                       0 );
        glBindTexture ( GL_TEXTURE_2D, 0 );
}

void hw_surface::_setup_vao()
{
        glBindVertexArray ( _vao );
        glActiveTexture ( GL_TEXTURE0 );
        glBindBuffer ( GL_ARRAY_BUFFER, _vbo );
        glVertexAttribPointer ( _position_attrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof ( GLfloat ), ( GLvoid* ) 0 );
        glVertexAttribPointer ( _texcoord_attrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof ( GLfloat ), ( GLvoid* ) ( 3 * sizeof ( GLfloat ) ) );
        glEnableVertexAttribArray ( _position_attrib );
        glEnableVertexAttribArray ( _texcoord_attrib );
        glBindVertexArray ( 0 );
}


void hw_surface::_copy_source_to_texture()
{
        _pbo_index = ++_pbo_index < _pbo_count ? _pbo_index : 0;
        glBindBuffer ( GL_PIXEL_UNPACK_BUFFER, _pbo[_pbo_index] );
        glBufferData ( GL_PIXEL_UNPACK_BUFFER, _source->w * _source->h * _source->format->BytesPerPixel, 0, GL_STREAM_DRAW );
        GLubyte* data_ptr = ( GLubyte* ) glMapBuffer ( GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY );
        if ( data_ptr ) {
                if ( _palette ) {
                        for ( int i = 0; i < _source->w * _source->h; i++ ) {
                                data_ptr[i] = _palette[ ( ( Uint8* ) _source->pixels ) [i]];
                        }
                } else {
                        memcpy ( data_ptr, _source->pixels, _source->w * _source->h * _source->format->BytesPerPixel );
                }

                glUnmapBuffer ( GL_PIXEL_UNPACK_BUFFER );

                glBindTexture ( GL_TEXTURE_2D, _texture );
                glTexSubImage2D ( GL_TEXTURE_2D,
                                  0,
                                  0,
                                  0,
                                  _source->w,
                                  _source->h,
                                  _pixel_format,
                                  _pixel_type,
                                  0 );

                glBindTexture ( GL_TEXTURE_2D, 0 );
        } else {
                printf ( "Unable to map PBO buffer.\n" );
                print_gl_error ( __FILE__, __LINE__ );
        }

        glBindBuffer ( GL_PIXEL_UNPACK_BUFFER, 0 );
}

void hw_surface::_copy_source_to_texture ( int numrects, SDL_Rect* rects )
{
        _pbo_index = ++_pbo_index < _pbo_count ? _pbo_index : 0;
        glBindBuffer ( GL_PIXEL_UNPACK_BUFFER, _pbo[_pbo_index] );
        glBufferData ( GL_PIXEL_UNPACK_BUFFER, _source->w * _source->h * _source->format->BytesPerPixel, 0, GL_STREAM_DRAW );
        GLubyte* data_ptr = ( GLubyte* ) glMapBuffer ( GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY );
        if ( data_ptr ) {
                GLint xmin = _source->w;
                GLint xmax = 0;
                GLint ymin = _source->h;
                GLint ymax = 0;

                for ( int i = 0; i < numrects; i++ ) {
                        xmin = xmin < rects[i].x ? xmin : rects[i].x;
                        xmax = xmax > rects[i].x + rects[i].w ? xmax : rects[i].x + rects[i].w;
                        ymin = ymin < rects[i].y ? ymin : rects[i].y;
                        ymax = ymax > rects[i].y + rects[i].h ? ymax : rects[i].y + rects[i].h;
                }

                xmin -= xmin % 2;
                xmax += xmax % 2;
                ymin -= ymin % 2;
                ymax += ymax % 2;

                xmin = xmin > 0 ? xmin : 0;
                ymin = ymin > 0 ? ymin : 0;
                xmax = xmax < _source->w ? xmax : _source->w;
                ymax = ymax < _source->h ? ymax : _source->h;

                GLint range_width = ( xmax - xmin ) * _source->format->BytesPerPixel;

                for ( int y = 0; y < ( ymax - ymin ); y++ ) {
                        memcpy ( data_ptr + y * range_width, ( ( GLubyte* ) _source->pixels ) + ( ( ymin + y ) * _source->w + xmin ) * _source->format->BytesPerPixel, range_width );
                }

                glUnmapBuffer ( GL_PIXEL_UNPACK_BUFFER );

                glBindTexture ( GL_TEXTURE_2D, _texture );
                glTexSubImage2D ( GL_TEXTURE_2D,
                                  0,
                                  xmin,
                                  ymin,
                                  xmax - xmin,
                                  ymax - ymin,
                                  _pixel_format,
                                  _pixel_type,
                                  0 );

                glBindTexture ( GL_TEXTURE_2D, 0 );
        } else {
                printf ( "Unable to map PBO buffer.\n" );
                print_gl_error ( __FILE__, __LINE__ );
        }
        glBindBuffer ( GL_PIXEL_UNPACK_BUFFER, 0 );
}

void hw_surface::_setup_program()
{
        _vertex_shader = compile_shader ( "../shaders/default.vert", GL_VERTEX_SHADER );
        _fragment_shader = compile_shader ( "../shaders/default.frag", GL_FRAGMENT_SHADER );
        link_program ( _shader_program, _vertex_shader, _fragment_shader );
        glDeleteShader ( _vertex_shader );
        glDeleteShader ( _fragment_shader );

        _position_attrib = glGetAttribLocation ( _shader_program, "position" );
        _texcoord_attrib = glGetAttribLocation ( _shader_program, "texcoord" );
        _texunit_uniform = glGetUniformLocation ( _shader_program, "texture_unit" );
        _ratio_uniform = glGetUniformLocation ( _shader_program, "res_ratio" );
}

void hw_surface::_create_palette()
{
        SDL_Palette *pal = _source->format->palette;
        _palette = new Uint32[pal->ncolors];
        for ( int i = 0; i < pal->ncolors; i++ ) {
                _palette[i] = sdl::SDL_MapRGB ( _target->format,
                                           pal->colors[i].r,
                                           pal->colors[i].g,
                                           pal->colors[i].b
                                         );
        }
}
}
