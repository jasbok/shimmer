#include "video.hpp"

SDL_Window *src_window = nullptr;
SDL_Renderer *src_renderer = nullptr;

SDL_Window *dest_window = nullptr;
SDL_Renderer *dest_renderer = nullptr;

SDL_GLContext gl_context;

void shims_sdl2::process_window_resize ( SDL_Event* event )
{
        if ( event->window.event == SDL_WINDOWEVENT_RESIZED && event->window.windowID == SDL_GetWindowID(dest_window)) {
                shimmer_->video()->resize ( shimmer_->video()->application_resolution(), {
                        static_cast<unsigned int> ( event->window.data1 ),
                        static_cast<unsigned int> ( event->window.data2 )
                } );
        }
}

void shims_sdl2::setup_video()
{
        int width, height;
        SDL_GetWindowSize ( src_window, &width, &height );

        shimmer_->video()->resize ( {
                static_cast<unsigned int> ( width ),
                static_cast<unsigned int> ( height )
        }, {
                static_cast<unsigned int> ( width ),
                static_cast<unsigned int> ( height )
        } );

        printf("Setting up video: %ix%i\n", width, height);
        
        auto pixel_format = shimmer::pixel_format::BGRA;
        auto pixel_type = shimmer::pixel_type::UNSIGNED_BYTE;

        shimmer_->video()->bpp ( 32 )
        .pixel_format ( pixel_format )
        .pixel_type ( pixel_type )
        .setup();
}

SDL_Window * SDL_CreateWindow ( const char* title, int x, int y, int w, int h, Uint32 flags )
{
        SHIM_LOG();
        SDL_Window* ret = sym::SDL_CreateWindow ( title, x, y, w, h, flags | SDL_WINDOW_OPENGL );

        if(src_window == nullptr){
                src_window = ret;
                dest_window = sym::SDL_CreateWindow ( title, x, y, w, h, flags | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL );
                SDL_SetWindowTitle(dest_window, "SHIM");
                //gl_context = SDL_GL_CreateContext(src_window);
        }

        return ret;
}

SDL_Window * SDL_CreateWindowFrom ( const void* data )
{
        SHIM_LOG();
        SDL_Window* ret = sym::SDL_CreateWindowFrom ( data );

        if(src_window == nullptr){
                src_window = ret;
                SDL_HideWindow(ret);
                dest_window = sym::SDL_CreateWindowFrom ( data );
                SDL_SetWindowTitle(dest_window, "SHIM");
        }
        return ret;
}

int SDL_CreateWindowAndRenderer ( int width, int height, Uint32 window_flags, SDL_Window ** window, SDL_Renderer ** renderer )
{
        SHIM_LOG();
        int ret = sym::SDL_CreateWindowAndRenderer ( width, height, window_flags | SDL_WINDOW_HIDDEN, window, renderer );

        if(src_window == nullptr){
                src_window = *window;
                src_renderer = *renderer;
                sym::SDL_CreateWindowAndRenderer ( width, height, window_flags | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL, &dest_window, &dest_renderer );
                SDL_SetWindowTitle(dest_window, "SHIM");
        }
        shims_sdl2::setup_video();
        return ret;
}

SDL_Renderer * SDL_CreateRenderer ( SDL_Window* window, int index, Uint32 flags )
{
        SHIM_LOG();
        SDL_Renderer* ret = sym::SDL_CreateRenderer ( window, index, flags );
        if ( window == src_window ) {
                src_renderer = ret;
                dest_renderer = sym::SDL_CreateRenderer ( dest_window, index, flags );
                shims_sdl2::setup_video();
        }
        return ret;
}

SDL_Renderer * SDL_CreateSoftwareRenderer ( SDL_Surface* surface )
{
        SHIM_LOG();
        SDL_Renderer* ret =sym::SDL_CreateSoftwareRenderer ( surface );
        if ( surface == SDL_GetWindowSurface ( src_window ) ) {
                src_renderer = ret;
                shims_sdl2::setup_video();
        }
        return ret;
}

void SDL_RenderPresent ( SDL_Renderer* renderer )
{
        SHIM_LOG();
        if(renderer == src_renderer){
                printf("Presenting renderer...\n");
                shimmer_->video()->bind_source_fbo();
                sym::SDL_RenderPresent ( src_renderer );
                //SDL_GL_MakeCurrent(dest_window, gl_context);
                shimmer_->video()->render();
                sym::SDL_RenderPresent ( dest_renderer );
                //SDL_GL_MakeCurrent(src_window, gl_context);
        }
        else{
                sym::SDL_RenderPresent ( renderer );
        }
}

SDL_GLContext SDL_GL_CreateContext(SDL_Window* window)
{
        SHIM_LOG();
        return sym::SDL_GL_CreateContext(window);
}

int SDL_UpdateWindowSurface ( SDL_Window* window )
{
        SHIM_LOG();
        return sym::SDL_UpdateWindowSurface ( window );
}

int SDL_UpdateWindowSurfaceRects ( SDL_Window* window, const SDL_Rect* rects, int numrects )
{
        SHIM_LOG();
        return sym::SDL_UpdateWindowSurfaceRects ( window, rects, numrects );
}

int SDL_RenderDrawRect ( SDL_Renderer* renderer, const SDL_Rect* rect )
{
        SHIM_LOG();
        return sym::SDL_RenderDrawRect ( renderer, rect );
}

int SDL_RenderDrawRects ( SDL_Renderer* renderer, const SDL_Rect* rects, int count )
{
        SHIM_LOG();
        return sym::SDL_RenderDrawRects ( renderer, rects, count );
}

int SDL_RenderCopy ( SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect )
{
        SHIM_LOG();
        return sym::SDL_RenderCopy ( renderer, texture, srcrect, dstrect );
}

int SDL_RenderCopyEx ( SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip )
{
        SHIM_LOG();
        return sym::SDL_RenderCopyEx ( renderer, texture, srcrect, dstrect, angle, center, flip );
}
