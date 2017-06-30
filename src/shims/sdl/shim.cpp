#include "shim.hpp"
#include "video.hpp"
#include <stdio.h>

class::shimmer::shimmer* shimmer_ = nullptr;

int SDL_Init ( Uint32 flags )
{
    SHIM_LOG();
    auto result = sym::SDL_Init ( flags );

    if ( shimmer_ ) {
        delete shimmer_;
    }

    shimmer_ = new shimmer::shimmer();

    return result;
}

void SDL_Quit()
{
    SHIM_LOG();

    if ( shimmer_ ) {
        delete shimmer_;
    }
}

SDL_GrabMode SDL_WM_GrabInput ( SDL_GrabMode mode )
{
    SHIM_LOG();

    //return sym::SDL_WM_GrabInput ( SDL_GRAB_OFF );
    return sym::SDL_WM_GrabInput ( mode );
}
