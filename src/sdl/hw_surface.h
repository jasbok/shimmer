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
        virtual void update(int numrects, SDL_Rect* rects);
        virtual void resize();

private:
        SDL_Surface *_source;
        SDL_Surface *_target;

        GLenum _pixel_format;
        GLenum _pixel_type;
        
        GLuint _vbo;
        GLuint _pbo[2];
        int _pbo_index;
        GLuint _vao;

        GLuint _texture;
        GLint _texture_uniform;
        
        GLuint _vertex_shader;
        GLuint _fragment_shader;
        GLuint _shader_program;

        Uint32 *_palette;
        
private:
        void _init();
        void _gl_init();
        void _setup_buffers();
        void _setup_textures();
        void _compile_program();
        void _copy_source_to_texture();
        void _copy_source_to_texture(int numrects, SDL_Rect* rects);
        void _copy_source_to_texture_original();
        void _render_texture();
        void _draw_quad();
        void _create_palette();
};

#endif
