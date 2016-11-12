#ifndef SHIMS_SDL_MOUSE_HPP
#define SHIMS_SDL_MOUSE_HPP

#include "shim.hpp"

SHIM ( Uint8, SDL_GetMouseState, int* x, int* y );
SHIM ( Uint8, SDL_GetRelativeMouseState, int* x, int* y );
SHIM ( void, SDL_WarpMouse, Uint16 x, Uint16 y );

namespace shims_sdl
{
void process_mouse ( SDL_Event* event );
}
#endif
