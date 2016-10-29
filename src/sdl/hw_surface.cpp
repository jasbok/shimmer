#include "hw_surface.h"

#include "sdl_shim.h"
#include "opengl_helpers.h"
#include <SDL/SDL_image.h>

#include <stdlib.h>

hw_surface::hw_surface ( SDL_Surface* source, SDL_Surface* target )
    : _source ( source ), _target( target ), _pbo_index(0), _palette(nullptr)
{
    _init();
}

hw_surface::~hw_surface()
{
    glDeleteTextures ( 1, &_texture );
    glDeleteProgram ( _shader_program );

    if(_palette) {
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

void hw_surface::update(int numrects, SDL_Rect* rects)
{
    _copy_source_to_texture(numrects, rects);
    _draw_quad();
}


void hw_surface::resize()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,_target->w,_target->h);
}

void hw_surface::_init()
{
    switch(_source->format->BitsPerPixel) {
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
    printf("==> Initialising OpenGL...\n");
    glewExperimental = true;
    glewInit();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    _setup_buffers();
    _setup_textures();
    _compile_program();

    glGenVertexArrays ( 1, &_vao );
    glBindVertexArray ( _vao );

    glUseProgram ( _shader_program );

    GLuint position_attrib = glGetAttribLocation ( _shader_program, "position" );
    GLuint texcoord_attrib = glGetAttribLocation ( _shader_program, "texcoord" );
    GLuint texture_uniform = glGetUniformLocation ( _shader_program, "texture_unit" );

    glEnableVertexAttribArray ( position_attrib );
    glEnableVertexAttribArray ( texcoord_attrib );
    glActiveTexture ( GL_TEXTURE0 );
    glUniform1i ( texture_uniform, 0 );
    glBindBuffer ( GL_ARRAY_BUFFER, _vbo );
    glVertexAttribPointer ( position_attrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof ( GLfloat ), ( GLvoid* ) 0 );
    glVertexAttribPointer ( texcoord_attrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof ( GLfloat ), ( GLvoid* ) ( 3 * sizeof ( GLfloat ) ) );

    //glDisableVertexAttribArray ( position_attrib );
    //glDisableVertexAttribArray ( texcoord_attrib );

    glBindVertexArray ( 0 );
}

void hw_surface::_render_texture()
{
    glActiveTexture ( GL_TEXTURE0 );
    glUniform1i ( _texture_uniform, 0 );
    glBindTexture ( GL_TEXTURE_2D, _texture );
}

void hw_surface::_draw_quad()
{
    glBindTexture ( GL_TEXTURE_2D, _texture );
    glBindVertexArray ( _vao );
    glDrawArrays ( GL_QUADS, 0, 4 );
    glBindVertexArray ( 0 );
    sdl::SDL_GL_SwapBuffers();
}

void hw_surface::_setup_buffers()
{
    GLfloat screen_vertices[] = {
        1.0,   1.0,   0.0,        1.0, 0.0,
        1.0,   -1.0,  0.0,        1.0, 1.0,
        -1.0,  -1.0,  0.0,        0.0, 1.0,
        -1.0,  1.0,   0.0,        0.0, 0.0
    };

    glGenBuffers ( 1, &_vbo );
    glBindBuffer ( GL_ARRAY_BUFFER, _vbo );
    glBufferData ( GL_ARRAY_BUFFER, sizeof ( screen_vertices ), screen_vertices, GL_STATIC_DRAW );
    glBindBuffer ( GL_ARRAY_BUFFER, 0 );

    for(int i = 0; i < 2; i++) {
        glGenBuffers (1, &_pbo[i]);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, _pbo[i]);
        glBufferData(GL_PIXEL_UNPACK_BUFFER, _source->w * _source->h * _source->format->BitsPerPixel * 0.125, 0, GL_STREAM_DRAW );
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }
}

void hw_surface::_setup_textures()
{
    glGenTextures ( 1, &_texture );
    glBindTexture ( GL_TEXTURE_2D, _texture );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    //glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

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

void hw_surface::_copy_source_to_texture()
{
    _pbo_index = !_pbo_index;
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, _pbo[_pbo_index]);

    GLubyte* data_ptr = (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
    if(data_ptr) {
        if(_palette) {
            //printf("target bpp: %u\n", _target->format->BitsPerPixel);
            for(int i = 0; i < _source->w * _source->h; i++) {
                data_ptr[i] = _palette[((Uint8*)_source->pixels)[i]];
            }
        }
        else {
            memcpy(data_ptr, _source->pixels, _source->w * _source->h * _source->format->BitsPerPixel * 0.125);
        }

        glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);

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
    }
    else {
        printf("Unable to map PBO buffer.\n");
    }

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

void hw_surface::_copy_source_to_texture(int numrects, SDL_Rect* rects)
{
    _pbo_index = !_pbo_index;
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, _pbo[_pbo_index]);

    GLubyte* data_ptr = (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
    if(data_ptr) {
        GLint xmin = _source->w;
        GLint xmax = 0;
        GLint ymin = _source->h;
        GLint ymax = 0;

        for(int i = 0; i < numrects; i++) {
            xmin = xmin < rects[i].x ? xmin : rects[i].x;
            xmax = xmax > rects[i].x + rects[i].w ? xmax : rects[i].x + rects[i].w;
            ymin = ymin < rects[i].y ? ymin : rects[i].y;
            ymax = ymax > rects[i].y + rects[i].h ? ymax : rects[i].y + rects[i].h;
        }
        //printf("Final: (%u,%u) -> (%u,%u)\n", xmin, ymin, xmax, ymax);

        xmin -= xmin % 2;
        xmax += xmax % 2;
        ymin -= ymin % 2;
        ymax += ymax % 2;

        xmin = xmin > 0 ? xmin : 0;
        ymin = ymin > 0 ? ymin : 0;
        xmax = xmax < _source->w ? xmax : _source->w;
        ymax = ymax < _source->h ? ymax : _source->h;

        GLint bytes = _source->format->BitsPerPixel * 0.125;
        GLint range_width = (xmax - xmin) * bytes;

        for(int y = 0; y < (ymax - ymin); y++) {
            memcpy(data_ptr + y * range_width, ((GLubyte*)_source->pixels) + ((ymin + y) * _source->w + xmin) * bytes, range_width);
        }

        glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);

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

        print_gl_error(__FILE__, __LINE__);
    }
    else {
        printf("Unable to map PBO buffer.\n");
    }
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

void hw_surface::_copy_source_to_texture_original() {
    glBindTexture ( GL_TEXTURE_2D, _texture );
    glTexImage2D ( GL_TEXTURE_2D,
                   0,
                   GL_RGB,
                   _source->w,
                   _source->h,
                   0,
                   _source->format->BitsPerPixel == 32 ? GL_BGRA : GL_RGB,
                   _source->format->BitsPerPixel == 32 ? GL_UNSIGNED_BYTE : GL_UNSIGNED_SHORT_5_6_5,
                   _source->pixels );
    glBindTexture ( GL_TEXTURE_2D, 0 );
}

void hw_surface::_compile_program()
{
    _vertex_shader = compile_shader ( "../shaders/default.vert", GL_VERTEX_SHADER );
    _fragment_shader = compile_shader ( "../shaders/default.frag", GL_FRAGMENT_SHADER );
    _shader_program = link_program ( _vertex_shader, _fragment_shader );
    glDeleteShader ( _vertex_shader );
    glDeleteShader ( _fragment_shader );
}

void hw_surface::_create_palette()
{
    SDL_Palette *pal = _source->format->palette;
    _palette = new Uint32[pal->ncolors];
    for(int i = 0; i < pal->ncolors; i++) {
        _palette[i] = SDL_MapRGB(_target->format,
                                 pal->colors[i].r,
                                 pal->colors[i].g,
                                 pal->colors[i].b
                                );
    }
}

