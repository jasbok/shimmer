#ifndef VIDEO_SURFACE_H
#define VIDEO_SURFACE_H

#include <SDL.h>

#include "config.h"

namespace shimmer
{
class video_surface
{
public:
        virtual ~video_surface() {}

        virtual void source ( SDL_Surface* source ) = 0;
        virtual SDL_Surface* source() = 0;
        virtual void target ( SDL_Surface* target ) = 0;
        virtual SDL_Surface* target() = 0;
        virtual void update() = 0;
        virtual void update ( int numrects, SDL_Rect* rects ) = 0;
        virtual void refresh() = 0;
        virtual void resize() = 0;
        virtual void set_config ( config config ) = 0;
};
}

#endif
