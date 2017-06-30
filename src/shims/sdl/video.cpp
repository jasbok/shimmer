#include "video.hpp"

SDL_Surface* source = nullptr;

SDL_Surface* target = nullptr;

std::vector<shimmer::rectangle<>> update_queue;

unsigned long ticks = 0;

namespace shims_sdl
{
void process_window_resize ( SDL_Event* event )
{
    shimmer_->video()->resize ( {
        static_cast<unsigned int> ( source->w ),
        static_cast<unsigned int> ( source->h )
    }, {
        static_cast<unsigned int> ( event->resize.w ),
        static_cast<unsigned int> ( event->resize.h )
    } );

    if ( shimmer_->video()->video_resolution() != shimmer::dimensions<> (
                target->w,
                target->h ) ) {
        target = sym::SDL_SetVideoMode (
                     shimmer_->video()->video_resolution().w,
                     shimmer_->video()->video_resolution().h,
                     32,
                     SDL_RESIZABLE | SDL_OPENGL );
    }

    // Do not propagate resize event to application
    event->active.type = SDL_NOEVENT;
}

void check_updates()
{
    if ( !update_queue.empty() && do_update() ) {
        shimmer_->video()->update ( source->pixels, update_queue );
        update_queue.clear();
        sym::SDL_GL_SwapBuffers();
    }
}

bool do_update()
{
    auto curr = SDL_GetTicks();
    if ( ( curr - ticks ) > 1000 / 59 ) {
        ticks = curr;
        return true;
    }
    return false;
}

void do_full_update()
{
    shimmer_->video()->update ( source->pixels );
    sym::SDL_GL_SwapBuffers();
    ticks = SDL_GetTicks();
    update_queue.clear();
}
}

SDL_Surface* SDL_SetVideoMode ( int width, int height, int bpp, Uint32 flags )
{
    SHIM_LOG();

    bpp = bpp == 0 ? 32 : bpp;

    auto pixel_format = bpp == 16
                        ? shimmer::pixel_format::RGB
                        : shimmer::pixel_format::BGRA;

    auto pixel_type = bpp == 16
                      ? shimmer::pixel_type::UNSIGNED_SHORT_5_6_5
                      : shimmer::pixel_type::UNSIGNED_BYTE;

    if ( source ) {
        sym::SDL_FreeSurface ( source );
    }

    source = SDL_CreateRGBSurface ( flags, width, height, bpp, 0,0,0,0 );

    if ( target ) {
        target = sym::SDL_SetVideoMode ( target->w,
                                         target->h,
                                         32,
                                         SDL_RESIZABLE | SDL_OPENGL );
    } else {
        target = sym::SDL_SetVideoMode ( width,
                                         height,
                                         32,
                                         SDL_RESIZABLE | SDL_OPENGL );
    }

    shimmer_->video()->resize ( {
        static_cast<unsigned int> ( source->w ),
        static_cast<unsigned int> ( source->h )
    }, {
        static_cast<unsigned int> ( target->w ),
        static_cast<unsigned int> ( target->h )
    } );

    shimmer_->video()->bpp ( bpp )
    .pixel_format ( pixel_format )
    .pixel_type ( pixel_type );

    shimmer_->video()->setup();
    update_queue.clear();

    return source;
}

SDL_Surface* SDL_GetVideoSurface()
{
    SHIM_LOG();
    return source;
}


int SDL_Flip ( SDL_Surface* screen )
{
    SHIM_LOG();
    shims_sdl::do_full_update();

    return 0;
}

void SDL_GL_SwapBuffers()
{
    SHIM_LOG();
    shims_sdl::do_full_update();
}


void SDL_UpdateRect (
    SDL_Surface* screen,
    Sint32 x,
    Sint32 y,
    Sint32 w,
    Sint32 h )
{
    SHIM_LOG();
    sym::SDL_UpdateRect ( screen, x, y, w, h );

    if ( screen == source && shims_sdl::do_update() ) {
        shimmer_->video()->update ( source->pixels, {
            {   {x, y},{
                    static_cast<unsigned int> ( w ) ,
                    static_cast<unsigned int> ( h )
                }
            }
        } );

        sym::SDL_GL_SwapBuffers();
    }
}

void SDL_UpdateRects ( SDL_Surface* screen, int numrects, SDL_Rect* rects )
{
    SHIM_LOG();
    sym::SDL_UpdateRects ( screen, numrects, rects );
    if ( screen == source ) {
        for ( int i = 0; i < numrects; i++ ) {
            update_queue.push_back ( {
                { rects[i].x, rects[i].y },
                { rects[i].w, rects[i].h }
            } );
        }

        if ( shims_sdl::do_update() ) {
            shimmer_->video()->update ( source->pixels, update_queue );
            update_queue.clear();
            sym::SDL_GL_SwapBuffers();
        }
    }
}

int SDL_UpperBlit (
    SDL_Surface* src,
    SDL_Rect* srcrect,
    SDL_Surface* dst,
    SDL_Rect* dstrect )
{
    SHIM_LOG();
    int result = sym::SDL_UpperBlit ( src, srcrect, dst, dstrect );

    if ( dst == source ) {
        if ( dstrect ) {
            update_queue.push_back ( {
                { dstrect->x, dstrect->y },
                { dstrect->w, dstrect->h }
            } );
        } else {
            update_queue.push_back ( {
                { 0, 0 },
                {
                    static_cast<unsigned int> ( source->w ),
                    static_cast<unsigned int> ( source->h )
                }
            } );
        }

        if ( shims_sdl::do_update() ) {
            shimmer_->video()->update ( source->pixels, update_queue );
            update_queue.clear();
            sym::SDL_GL_SwapBuffers();
        }
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
