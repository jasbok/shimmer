#include "../shim_macros.h"
#include "scaled_window.h"

#include <SDL.h>
#include <iostream>

Scaled_Window scaled_window;


// SHIM ( int, SDL_Init, Uint32 flags )
// {
//         DLSYM ( SDL_Init );
//         return HANDLE ( flags );
// }
// 
// SHIM ( int, SDL_UpdateWindowSurface, SDL_Window* window )
// {
//         DLSYM ( SDL_UpdateWindowSurface );
//         return HANDLE ( window );
// }
// 
// SHIM ( SDL_Window*, SDL_CreateWindow, const char *title,
//        int x, int y, int w,
//        int h, Uint32 flags )
// {
//         DLSYM ( SDL_CreateWindow );
//         SDL_Window* window = HANDLE ( title, x, y, w, h, flags );
//         scaled_window.window(HANDLE ( title, x, y, 1920, 1080, flags ));
//         scaled_window.source_window(window);
//         return window;
// }
// 
// SHIM ( int, SDL_CreateWindowAndRenderer,
//        int            w,
//        int            h,
//        Uint32         flags,
//        SDL_Window**   window,
//        SDL_Renderer** renderer )
// {
//         DLSYM ( SDL_CreateWindowAndRenderer );
//         return HANDLE ( w, h, flags, window, renderer );
// }
// 
// SHIM ( void, SDL_DestroyWindow, SDL_Window* window )
// {
//         DLSYM ( SDL_DestroyWindow );
//         HANDLE ( scaled_window.window() );
//         HANDLE ( window );
// }
// 
// SHIM ( SDL_Renderer*, SDL_CreateRenderer, SDL_Window* window, int index, Uint32 flags )
// {
//         DLSYM ( SDL_CreateRenderer );
//         SDL_Renderer* renderer = HANDLE ( window, index, flags );
//         scaled_window.renderer(HANDLE ( scaled_window.window(), index, flags ));
//         scaled_window.source_renderer(renderer);
//         return renderer;
// }
// 
// 
// SHIM ( void, SDL_DestroyRenderer, SDL_Renderer* renderer )
// {
//         DLSYM ( SDL_DestroyRenderer );
//         HANDLE ( scaled_window.renderer() );
//         HANDLE ( renderer );
// }
// 
// SHIM ( void, SDL_RenderPresent, SDL_Renderer* renderer )
// {
//         DLSYM ( SDL_RenderPresent );
//         
//         scaled_window.render();
//         HANDLE(scaled_window.renderer());
//         HANDLE ( renderer );
//         
// }
// 
// SHIM ( int, SDL_SetRenderTarget, SDL_Renderer* renderer, SDL_Texture* texture )
// {
//         DLSYM ( SDL_SetRenderTarget );
//         return HANDLE ( renderer, texture );
// }
