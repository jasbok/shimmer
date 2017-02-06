#ifndef SHIMS_SDL2_MOUSE_HPP
#define SHIMS_SDL2_MOUSE_HPP

#include "shim.hpp"

SHIM ( Uint32, SDL_GetMouseState, int* x, int* y );
SHIM ( Uint32, SDL_GetRelativeMouseState, int* x, int* y );
SHIM ( void, SDL_WarpMouse, Uint16 x, Uint16 y );

namespace shims_sdl2
{
void process_mouse ( SDL_Event* event );
}
#endif
