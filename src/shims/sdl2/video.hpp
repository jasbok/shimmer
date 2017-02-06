#ifndef SHIMS_SDL2_VIDEO_HPP
#define SHIMS_SDL2_VIDEO_HPP

#include "shim.hpp"

namespace shims_sdl2{
        void process_window_resize ( SDL_Event* event );
        void setup_video();
}

SHIM ( SDL_Window*, SDL_CreateWindow,
       const char* title,
       int         x,
       int         y,
       int         w,
       int         h,
       Uint32      flags );

SHIM ( int, SDL_CreateWindowAndRenderer,
       int            width,
       int            height,
       Uint32         window_flags,
       SDL_Window**   window,
       SDL_Renderer** renderer );

SHIM ( SDL_Window*, SDL_CreateWindowFrom,
       const void* data );

SHIM ( int, SDL_UpdateWindowSurface,
       SDL_Window* window );

SHIM ( int, SDL_UpdateWindowSurfaceRects,
       SDL_Window*      window,
       const SDL_Rect*  rects,
       int              numrects );


SHIM ( SDL_Renderer*, SDL_CreateRenderer,
       SDL_Window* window,
       int         index,
       Uint32      flags );

SHIM ( SDL_Renderer*, SDL_CreateSoftwareRenderer,
       SDL_Surface* surface );

SHIM ( void, SDL_RenderPresent,
       SDL_Renderer* renderer );

SHIM ( SDL_GLContext, SDL_GL_CreateContext,SDL_Window* window);



SHIM ( int, SDL_RenderDrawRect,
       SDL_Renderer*   renderer,
       const SDL_Rect* rect );

SHIM ( int, SDL_RenderDrawRects,
       SDL_Renderer*   renderer,
       const SDL_Rect* rects,
       int             count );

SHIM ( int, SDL_RenderCopy,
       SDL_Renderer*   renderer,
       SDL_Texture*    texture,
       const SDL_Rect* srcrect,
       const SDL_Rect* dstrect );


SHIM ( int, SDL_RenderCopyEx,
       SDL_Renderer*          renderer,
       SDL_Texture*           texture,
       const SDL_Rect*        srcrect,
       const SDL_Rect*        dstrect,
       const double           angle,
       const SDL_Point*       center,
       const SDL_RendererFlip flip );

#endif
