#include "event.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
#include "video.hpp"

int SDL_PollEvent ( SDL_Event* event )
{
        SHIM_LOG();
        int result = sym::SDL_PollEvent ( event );
        shims_sdl::process_event (event);
        return result;
}

void shims_sdl::process_event(SDL_Event* event)
{
        if ( event && event->active.type == event->type ) {
                switch ( event->type ) {
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
        shims_sdl::check_updates();
}
