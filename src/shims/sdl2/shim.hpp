#ifndef SHIMS_SDL2_SHIM_HPP
#define SHIMS_SDL2_SHIM_HPP

#include "shimmer.hpp"
#include "../shim_macros.h"
#include <SDL.h>

extern class::shimmer::shimmer *shimmer_;

SHIM ( int, SDL_Init, Uint32 flags );
SHIM ( void, SDL_Quit, void );

#endif
