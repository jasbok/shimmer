#ifndef VIDEO_SURFACE_H
#define VIDEO_SURFACE_H

#include <SDL.h>

class video_surface{
public:
    
    virtual ~video_surface(){}
    
    virtual void source( SDL_Surface* source) = 0;
    virtual SDL_Surface* source() = 0;
    virtual void target ( SDL_Surface* target ) = 0;
    virtual SDL_Surface* target() = 0;
    virtual void update() = 0;
};

#endif
