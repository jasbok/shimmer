#include "hw_surface.h"

#include "sdl_shim.h"
#include "opengl_helpers.h"
#include <SDL/SDL_image.h>

hw_surface::hw_surface ( SDL_Surface* source, SDL_Surface* target )
        : _source ( source ), _target( target )
{
        _gl_init();
}

hw_surface::~hw_surface()
{
        glDeleteTextures ( 1, &_texture );
        glDeleteProgram ( _shader_program );
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
        glClearColor ( 0.9f, 0.15f, 0.15f, 1.0f );
        glClear ( GL_COLOR_BUFFER_BIT );

        _setup_buffers();
        //glUseProgram ( _shader_program );
        _copy_source_to_texture();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0,0,_target->w,_target->h);
        glBindTexture ( GL_TEXTURE_2D, _texture );

        glBindVertexArray ( _vao );
        glDrawArrays ( GL_QUADS, 0, 4 );
        glBindVertexArray ( 0 );

        sdl::SDL_GL_SwapBuffers();
}

void hw_surface::_gl_init()
{
        printf("==> Initialising OpenGL...\n");
        glewExperimental = true;
        glewInit();


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
}

void hw_surface::_setup_textures()
{
        glGenTextures ( 1, &_texture );
        glBindTexture ( GL_TEXTURE_2D, _texture );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        //glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glBindTexture ( GL_TEXTURE_2D, 0 );

        printf ( "::: Copy Texture Dimensions: %ix%ix%i.\n", _source->w, _source->h, _source->format->BitsPerPixel );
        printf ( "::: Copy Texture Format RED => Mask:%i Shift:%i Loss:%i.\n", _source->format->Rmask, _source->format->Rshift, _source->format->Rloss );
        printf ( "::: Copy Texture Format GREEN => Mask:%i Shift:%i Loss:%i.\n", _source->format->Gmask, _source->format->Gshift, _source->format->Gloss );
        printf ( "::: Copy Texture Format BLUE => Mask:%i Shift:%i Loss:%i.\n", _source->format->Bmask, _source->format->Bshift, _source->format->Bloss );
        printf ( "::: Copy Texture Format ALPHA => Mask:%i Shift:%i Loss:%i.\n", _source->format->Amask, _source->format->Ashift, _source->format->Aloss );
}

void hw_surface::_copy_source_to_texture()
{
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

