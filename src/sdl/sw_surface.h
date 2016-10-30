#ifndef SW_SURFACE_H
#define SW_SURFACE_H

#include "video_surface.h"

class sw_surface : public video_surface
{
public:
        sw_surface ( SDL_Surface* source, SDL_Surface* target );
        virtual ~sw_surface();

        virtual void source ( SDL_Surface* source );
        virtual SDL_Surface* source();
        virtual void target ( SDL_Surface* target );
        virtual SDL_Surface* target();
        virtual void update();
        virtual void update(int numrects, SDL_Rect* rects);
        virtual void resize();
        virtual void filtering(unsigned int level);
        virtual void keep_aspect_ratio(bool keep);

private:
        SDL_Surface *_source, *_target;
};

#endif
