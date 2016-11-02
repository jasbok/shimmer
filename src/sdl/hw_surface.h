#ifndef HW_SURFACE_H
#define HW_SURFACE_H

#include "video_surface.h"
#include <SDL.h>
#include <GL/glew.h>
#include <deque>

namespace shimmer
{
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
        virtual void update ( int numrects, SDL_Rect* rects );
        virtual void refresh();
        virtual void resize();
        virtual void set_config ( config config );

private:
        SDL_Surface *_source;
        SDL_Surface *_target;
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
        bool _keep_aspect_ratio;

        GLuint _vertex_shader;
        GLuint _fragment_shader;
        GLuint _shader_program;

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
