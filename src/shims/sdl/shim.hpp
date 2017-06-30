#ifndef SHIMS_SDL_SHIM_HPP
#define SHIMS_SDL_SHIM_HPP

#include "shimmer.hpp"
#include "../shim_macros.h"
#include <SDL.h>

extern class::shimmer::shimmer* shimmer_;

SHIM ( int, SDL_Init,
       Uint32 flags );

SHIM ( void, SDL_Quit,
       void );

SHIM ( SDL_GrabMode, SDL_WM_GrabInput,
       SDL_GrabMode mode );

#endif
