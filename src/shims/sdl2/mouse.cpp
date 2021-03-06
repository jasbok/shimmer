#include "mouse.hpp"

Uint32 SDL_GetMouseState ( int* x, int* y )
{
        SHIM_LOG();
        Uint8 result = sym::SDL_GetMouseState ( x, y );
        shimmer_->mouse()->transform(x, y);
        return result;
}

Uint32 SDL_GetRelativeMouseState ( int* x, int* y )
{
        SHIM_LOG();
        Uint8 result = sym::SDL_GetRelativeMouseState ( x, y );
        shimmer_->mouse()->transform(x, y);
        return result;
}

void SDL_WarpMouse ( Uint16 x, Uint16 y )
{
        SHIM_LOG();
        shimmer_->mouse()->transform_inverse(&x, &y);
        sym::SDL_WarpMouse ( x, y );
}

void shims_sdl2::process_mouse ( SDL_Event* event )
{
        shimmer_->mouse()->transform ( &event->motion.x, &event->motion.y );
        shimmer_->mouse()->transform( &event->motion.xrel, &event->motion.yrel );
}
