#ifndef HW_SURFACE_H
#define HW_SURFACE_H

#include "video_surface.h"
#include <SDL.h>
#include <GL/glew.h>

class hw_surface : public video_surface
{
public:
        hw_surface ( SDL_Surface* source, SDL_Surface* target );
        virtual ~hw_surface();

        virtual void source ( SDL_Surface* source );
        virtual SDL_Surface* source();
        virtual void target ( SDL_Surface* target );
        virtual SDL_Surface* target();
        virtual void update();

private:
        SDL_Surface *_source;
        SDL_Surface *_target;

        void _gl_init();
        void _setup_buffers();
        void _setup_textures();
        void _compile_program();
        void _copy_source_to_texture();
        void _render_texture();

        GLuint _vbo;
        GLuint _vertex_shader;
        GLuint _fragment_shader;
        GLuint _shader_program;
        GLuint _vao;

        GLuint _texture;
        GLint _texture_uniform;
};

#endif
