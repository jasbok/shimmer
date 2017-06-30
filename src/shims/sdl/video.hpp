#ifndef SHIMS_SDL_VIDEO_HPP
#define SHIMS_SDL_VIDEO_HPP

#include "shim.hpp"

namespace shims_sdl
{
void process_window_resize ( SDL_Event* event );

void check_updates();

bool do_update();

void do_full_update();
}

SHIM ( SDL_Surface*, SDL_SetVideoMode,
       int width,
       int height,
       int bpp,
       Uint32 flags );

SHIM ( SDL_Surface*, SDL_GetVideoSurface,
       void );

SHIM ( int, SDL_Flip,
       SDL_Surface* screen );

SHIM ( void, SDL_UpdateRect,
       SDL_Surface* screen,
       Sint32 x,
       Sint32 y,
       Sint32 w,
       Sint32 h );

SHIM ( void, SDL_UpdateRects,
       SDL_Surface* screen,
       int numrects,
       SDL_Rect* rects );

SHIM ( int, SDL_UpperBlit,
       SDL_Surface* src,
       SDL_Rect* srcrect,
       SDL_Surface* dst,
       SDL_Rect* dstrect );

SHIM ( int, SDL_FillRect,
       SDL_Surface* dst,
       SDL_Rect* dstrect,
       Uint32 color );

SHIM ( void, SDL_FreeSurface,
       SDL_Surface* surface );

SHIM ( void, SDL_GL_SwapBuffers,
       void );

#endif
