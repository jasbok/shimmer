#include "video.hpp"

SDL_Surface *source = nullptr;
SDL_Surface *target = nullptr;

SDL_Surface * SDL_SetVideoMode ( int width, int height, int bpp, Uint32 flags )
{
        SHIM_LOG();

        if ( source ) {
                sym::SDL_FreeSurface ( source );
        }
        //source = sdl::SDL_CreateRGBSurface ( flags, width, height, bpp, 0,0,0,0 );
        //target = sdl::SDL_SetVideoMode ( width, height, 32, SDL_RESIZABLE | SDL_OPENGL );
        source = sym::SDL_SetVideoMode ( width, height, bpp, flags | SDL_RESIZABLE );
        shimmer_->video_api()->source ( {static_cast<unsigned int> ( width ), static_cast<unsigned int> ( height ) } );
        shimmer_->video_api()->target ( {static_cast<unsigned int> ( width ), static_cast<unsigned int> ( height ) } );
        shimmer_->video_api()->setup();
        return source;
}

SDL_Surface * SDL_GetVideoSurface()
{
        SHIM_LOG();
        return source;
}


int SDL_Flip ( SDL_Surface* screen )
{
        SHIM_LOG();
        shimmer_->video_api()->update();
        return 0;
}

void SDL_GL_SwapBuffers()
{
        SHIM_LOG();
        shimmer_->video_api()->update();
}


void SDL_UpdateRect ( SDL_Surface* screen, Sint32 x, Sint32 y, Sint32 w, Sint32 h )
{
        SHIM_LOG();
        sym::SDL_UpdateRect ( screen, x, y, w, h );
        if ( screen == source ) {
                shimmer_->video_api()->update ( {{x, y},{ static_cast<unsigned int> ( w ) , static_cast<unsigned int> ( h ) }} );
        }
}

void SDL_UpdateRects ( SDL_Surface* screen, int numrects, SDL_Rect* rects )
{
        SHIM_LOG();

        sym::SDL_UpdateRects ( screen, numrects, rects );
        if ( screen == source ) {
                std::vector<shimmer::rectangle<>> srects ( numrects );
                for ( int i = 0; i < numrects; i++ ) {
                        srects.push_back ( { { rects[i].x, rects[i].y }, { rects[i].w, rects[i].h } } );
                }
                shimmer_->video_api()->update ( srects );
        }
}

int SDL_UpperBlit ( SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect )
{
        SHIM_LOG();
        int result = sym::SDL_UpperBlit ( src, srcrect, dst, dstrect );
        if ( dst == source ) {
                shimmer_->video_api()->update ( { { dstrect->x, dstrect->y }, { dstrect->w, dstrect->h } } );
        }
        return result;
}

int SDL_FillRect ( SDL_Surface* dst, SDL_Rect* dstrect, Uint32 color )
{
        SHIM_LOG();
        return sym::SDL_FillRect ( dst, dstrect, color );
}

void SDL_FreeSurface ( SDL_Surface* surface )
{
        SHIM_LOG();
        if ( surface == source ) {
                source = nullptr;
        }
        sym::SDL_FreeSurface ( surface );
}
