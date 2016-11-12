#include "shim.hpp"
#include <stdio.h>

class::shimmer::shimmer *shimmer_ = nullptr;
SDL_Surface *source = nullptr;
SDL_Surface *target = nullptr;

int SDL_Init ( Uint32 flags )
{
        SHIM_LOG();
        auto result = sym::SDL_Init ( flags );
        if ( shimmer_ )
                delete shimmer_;
        shimmer_ = new shimmer::shimmer();
        return result;
}

void SDL_Quit()
{
        SHIM_LOG();
        if ( shimmer_ ) delete shimmer_;
}


SDL_Surface * SDL_SetVideoMode ( int width, int height, int bpp, Uint32 flags )
{
        SHIM_LOG();

        if ( source ) {
                sym::SDL_FreeSurface ( source );
        }
        //source = sdl::SDL_CreateRGBSurface ( flags, width, height, bpp, 0,0,0,0 );
        //target = sdl::SDL_SetVideoMode ( width, height, 32, SDL_RESIZABLE | SDL_OPENGL );
        source = sym::SDL_SetVideoMode ( width, height, bpp, flags );
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

int SDL_LockSurface ( SDL_Surface* surface )
{
        SHIM_LOG();
        return sym::SDL_LockSurface ( surface );
}

void SDL_UnlockSurface ( SDL_Surface* surface )
{
        SHIM_LOG();
        sym::SDL_UnlockSurface ( surface );
}

void SDL_FreeSurface ( SDL_Surface* surface )
{
        SHIM_LOG();
        if ( surface == source ) {
                source = nullptr;
        }
        sym::SDL_FreeSurface ( surface );
}

SDL_GrabMode SDL_WM_GrabInput ( SDL_GrabMode mode )
{
        SHIM_LOG();
        return sym::SDL_WM_GrabInput ( mode );
}

int SDL_SetColorKey ( SDL_Surface* surface, Uint32 flag, Uint32 key )
{
        SHIM_LOG();
        return sym::SDL_SetColorKey ( surface, flag, key );
}


int SDL_SetAlpha ( SDL_Surface* surface, Uint32 flag, Uint8 alpha )
{
        SHIM_LOG();
        return sym::SDL_SetAlpha ( surface, flag, alpha );
}

SDL_Surface * SDL_DisplayFormat ( SDL_Surface* surface )
{
        SHIM_LOG();
        return sym::SDL_DisplayFormat ( surface );
}

SDL_Surface * SDL_CreateRGBSurface ( Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask )
{
        SHIM_LOG();
        return sym::SDL_CreateRGBSurface ( flags, width, height, depth, Rmask, Gmask, Bmask, Amask );
}

SDL_Surface * SDL_CreateRGBSurfaceFrom ( void* pixels, int width, int height, int depth, int pitch, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask )
{
        SHIM_LOG();
        return sym::SDL_CreateRGBSurfaceFrom ( pixels, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask );
}

Uint32 SDL_GetTicks()
{
        SHIM_LOG();
        return sym::SDL_GetTicks();
}

Uint32 SDL_MapRGB ( const SDL_PixelFormat* format,
                    Uint8                  r,
                    Uint8                  g,
                    Uint8                  b )
{
        SHIM_LOG();
        return sym::SDL_MapRGB ( format, r, g, b );
}
