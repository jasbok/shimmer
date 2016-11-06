#ifndef HW_SURFACE_H
#define HW_SURFACE_H

#include <SDL.h>
#include <GL/glew.h>
#include <deque>

namespace shimmer
{
class hw_surface
{
public:
        hw_surface ( SDL_Surface* source, SDL_Surface* target, GLuint shader_program );
        virtual ~hw_surface();

        virtual void source ( SDL_Surface* source );
        virtual SDL_Surface* source();
        virtual void target ( SDL_Surface* target );
        virtual SDL_Surface* target();
        virtual void shader_program ( GLuint shader_program );
        virtual GLuint shader_program();

        virtual void update();
        virtual void update ( int numrects, SDL_Rect* rects );
        virtual void refresh();
        virtual void resize();
        virtual void update_config ();

private:
        SDL_Surface *_source;
        SDL_Surface *_target;
        GLuint _shader_program;

        GLfloat _ratio_w, _ratio_h;

        GLenum _pixel_format;
        GLenum _pixel_type;

        GLuint _vbo;
        GLuint _vao;

        GLint _pbo_count;
        GLuint *_pbo;
        int _pbo_index;

        GLuint _texture;
        GLuint _texture_filter;

        GLuint _position_attrib;
        GLuint _texcoord_attrib;
        GLint _texunit_uniform;
        GLint _ratio_uniform;

        Uint32 *_palette;

        std::deque<SDL_Rect> _queue;
        Uint32 _update_ticks;

private:
        void _init();
        void _gl_init();

        void _setup_buffers();
        void _setup_textures();
        void _setup_program();
        void _setup_vao();
        void _copy_source_to_texture();
        void _copy_source_to_texture ( int numrects, SDL_Rect* rects );
        void _draw_quad();
        void _create_palette();
};
}

#endif
