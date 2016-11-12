#include "keyboard.hpp"

void shims_sdl::process_keyboard(SDL_Event* event)
{
//         switch ( event->key.keysym.sym ) {
//         case SDLK_LSUPER:
//         case SDLK_RSUPER:
//                 _user_mode = event->active.type == SDL_KEYDOWN;
//                 if ( _user_mode ) {
//                         sdl::SDL_WM_GrabInput ( SDL_GRAB_OFF );
//                 }
//                 break;
//         default:
//                 break;
//         }
// 
//         if ( _user_mode ) {
//                 if ( event->active.type == SDL_KEYUP ) {
//                         switch ( event->key.keysym.sym ) {
//                         case SDLK_l:
//                                 config::instance().next_filter_level();
//                                 _video->update_config();
//                                 break;
//                         case SDLK_a:
//                                 config::instance().toggle_keep_aspect_ratio();
//                                 _video->update_config();
//                                 break;
//                         case SDLK_s:
//                                 _menu_system.get(MENUS::FRAGMENT_SHADER_SELECTION).next()();
//                                 break;
//                         default:
//                                 break;
//                         }
//                 }
//         }

        // Check if keyboard events should be captured
        if(shimmer_->keyboard_api()->capture()){
                event->active.type = SDL_NOEVENT;
        }
}
