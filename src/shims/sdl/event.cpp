#include "event.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
#include "window.hpp"

int SDL_PollEvent ( SDL_Event* event )
{
        SHIM_LOG();
        int result = sym::SDL_PollEvent ( event );
        //shimmer_->process_event ( event );
        //shimmer_->video_api()->update();
        return result;
}

void shims_sdl::process_event(SDL_Event* event)
{
        if ( event ) {
                switch ( event->active.type ) {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                        process_keyboard ( event );
                        break;
                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEBUTTONDOWN:
                        process_mouse ( event );
                        break;
                case SDL_VIDEORESIZE:
                        process_window_resize ( event );
                        break;
                default:
                        break;
                }
        }
}
