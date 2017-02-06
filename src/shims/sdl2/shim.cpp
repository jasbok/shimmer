#include "shim.hpp"

class::shimmer::shimmer *shimmer_ = nullptr;

int SDL_Init ( Uint32 flags )
{
        SHIM_LOG();
        if ( shimmer_ )
                delete shimmer_;
        shimmer_ = new shimmer::shimmer();
        return sym::SDL_Init ( flags );
}

void SDL_Quit()
{
        SHIM_LOG();
        if(shimmer_) delete shimmer_;
        sym::SDL_Quit();
}
