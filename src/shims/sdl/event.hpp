#ifndef SHIMS_SDL_EVENT_HPP
#define SHIMS_SDL_EVENT_HPP

#include "shim.hpp"

SHIM ( int, SDL_PollEvent,
       SDL_Event* event );

SHIM ( Uint8, SDL_EventState,
       Uint8 type,
       int state );

namespace shims_sdl
{
void process_event ( SDL_Event* event );
}

#endif
