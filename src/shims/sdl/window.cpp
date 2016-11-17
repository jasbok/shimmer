#include "video.hpp"
#include "window.hpp"

void shims_sdl::process_window_resize ( SDL_Event* event )
{
        shimmer_->window()->resize ( {
                static_cast<unsigned int> ( event->resize.w ),
                static_cast<unsigned int> ( event->resize.h )
        } );

        // Do not propagate resize event to application
        event->active.type = SDL_NOEVENT;
}
