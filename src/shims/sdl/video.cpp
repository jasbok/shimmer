#include "video.hpp"

SDL_Surface *source = nullptr;
SDL_Surface *target = nullptr;

void update_video(){
        if(shimmer_->window()->dims() != shimmer::dimensions<>(target->w, target->h)){
                target = sym::SDL_SetVideoMode ( shimmer_->window()->dims().w, shimmer_->window()->dims().h, 32, SDL_RESIZABLE | SDL_OPENGL );
        }
        shimmer_->video()->pixels(source->pixels);
}


SDL_Surface * SDL_SetVideoMode ( int width, int height, int bpp, Uint32 flags )
{
        SHIM_LOG();

        if ( source ) {
                sym::SDL_FreeSurface ( source );
        }
        source = SDL_CreateRGBSurface ( flags, width, height, bpp, 0,0,0,0 );
        target = sym::SDL_SetVideoMode ( width, height, 32, SDL_RESIZABLE | SDL_OPENGL );

        auto pixel_format = bpp == 16 ? shimmer::pixel_format::RGB : shimmer::pixel_format::BGRA;
        auto pixel_type = bpp == 16 ? shimmer::pixel_type::UNSIGNED_SHORT_5_6_5 : shimmer::pixel_type::UNSIGNED_BYTE;

        shimmer_->video()
        ->source_dims ( {static_cast<unsigned int> ( width ), static_cast<unsigned int> ( height ) } )
        .target_dims ( {static_cast<unsigned int> ( width ), static_cast<unsigned int> ( height ) } )
        .bpp ( bpp )
        .pixel_format ( pixel_format )
        .pixel_type ( pixel_type )
        .setup();

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
        update_video();
        shimmer_->video()->update();
        sym::SDL_GL_SwapBuffers();
        return 0;
}

void SDL_GL_SwapBuffers()
{
        SHIM_LOG();
        update_video();
        shimmer_->video()->update();
        sym::SDL_GL_SwapBuffers();
}


void SDL_UpdateRect ( SDL_Surface* screen, Sint32 x, Sint32 y, Sint32 w, Sint32 h )
{
        SHIM_LOG();
        sym::SDL_UpdateRect ( screen, x, y, w, h );
        if ( screen == source ) {
                update_video();
                shimmer_->video()->update ( {{x, y},{ static_cast<unsigned int> ( w ) , static_cast<unsigned int> ( h ) }} );
                sym::SDL_GL_SwapBuffers();
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
                update_video();
                shimmer_->video()->update ( srects );
                sym::SDL_GL_SwapBuffers();
        }
}

int SDL_UpperBlit ( SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect )
{
        SHIM_LOG();
        int result = sym::SDL_UpperBlit ( src, srcrect, dst, dstrect );
        if ( dst == source ) {
                update_video();
                if ( dstrect ) {
                        shimmer_->video()->update ( { { dstrect->x, dstrect->y }, { dstrect->w, dstrect->h } } );
                } else {
                        shimmer_->video()->update();
                }
                sym::SDL_GL_SwapBuffers();
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
