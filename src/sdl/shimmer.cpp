#include "shimmer.h"
#include "sdl_shim.h"

namespace shimmer
{
shimmer::shimmer()
        : _w ( 0 ), _h ( 0 ), _bpp ( 32 ),
          _video_flags ( 0 ),
          _config (),

          _video ( nullptr ),
          _source ( nullptr ), _target ( nullptr ),
          _warp_factor_x ( 1 ), _warp_factor_y ( 1 ),

          _user_mode ( false )
{
        init();
}

shimmer::~shimmer()
{
        destroy();
}

//
//  CONFIGURATION AND RESOURCE MANAGEMENT
//
void shimmer::init()
{
        DLOG ( "Initialising Shimmer..." );
}

void shimmer::destroy()
{
        DLOG ( "Destroying Shimmer..." );
        if ( _video ) {
                delete _video;
        }
}

//
// VIDEO
//
void shimmer::setup_video()
{
        DLOG ( "Setting video..." );

        if ( _source->flags & SDL_OPENGL ) {
                printf ( "==> Application requested an OpenGL context." );
        }
        _configure_video_from_source();
        _create_video_surface();

        if ( _video ) delete _video;

        _video = new hw_surface ( _source, _target );
        _video->set_config ( _config );
}

void shimmer::update_video()
{
        if ( _video )
                _video->update();
}

void shimmer::update_video ( int numrects, SDL_Rect* rects )
{
        if ( _video )
                _video->update ( numrects, rects );
}

void shimmer::refresh_video()
{
        if ( _video )
                _video->refresh();
}

void shimmer::resize_video()
{
        DLOG ( "Resizing video..." );
        _create_video_surface();
        _video->resize();
}


//
// INPUT
//
void shimmer::process_event ( SDL_Event* event )
{
        if ( event ) {
                switch ( event->active.type ) {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                        _process_keyboard ( event );
                        break;
                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEBUTTONDOWN:
                        _process_mouse ( event );
                        break;
                case SDL_VIDEORESIZE:
                        _process_video_resize ( event );
                        break;
                default:
                        break;
                }
        }
}

void shimmer::warp_coord ( int* x, int* y )
{
        DLOG ( "Warping coordinates..." );
        if ( x ) *x = *x * _warp_factor_x;
        if ( y ) *y = *y * _warp_factor_y;
}

void shimmer::warp_coord ( Uint16* x, Uint16* y )
{
        DLOG ( "Warping coordinates..." );
        if ( x ) *x = *x * _warp_factor_x;
        if ( y ) *y = *y * _warp_factor_y;
}

//
// FIELD ACCESS
//
SDL_Surface * shimmer::source()
{
        //DLOG ( "Getting source... %p", _source );
        return _source;
}

void shimmer::source ( SDL_Surface* source )
{
        //DLOG ( "Setting source... %p", source );
        _source = source;
}

SDL_Surface * shimmer::target()
{
        //DLOG ( "Getting target... %p", _target );
        return _target;
}

//
//  PRIVATE: VIDEO
//
void shimmer::_configure_video_from_source()
{
        DLOG ( "Configure video from source..." );

        if ( !_w ) _w = _source->w;
        if ( !_h ) _h = _source->h;
}

void shimmer::_create_video_surface()
{
        DLOG ( "Create video surface..." );

        // Do not allow the window to resize into nothing.
        _w = _w > 50 ? _w : 50;
        _h = _h > 50 ? _h: 50;

        _target = sdl::SDL_SetVideoMode ( _w, _h, _bpp, _video_flags | SDL_RESIZABLE | SDL_OPENGL );
        glewExperimental = true;
        glewInit();

        _calculate_warp_factor();
}

//
// PRIVATE: INPUT
//
void shimmer::_calculate_warp_factor()
{
        DLOG ( "Calculate warp factor..." );
        _warp_factor_x = _source->w / ( float ) ( _target->w );
        _warp_factor_y = _source->h / ( float ) ( _target->h );
}

void shimmer::_process_keyboard ( SDL_Event* event )
{
        DLOG ( "Process keyboard..." );
        switch ( event->key.keysym.sym ) {
        case SDLK_LSUPER:
        case SDLK_RSUPER:
                _user_mode = event->active.type == SDL_KEYDOWN;
                if ( _user_mode ) {
                        sdl::SDL_WM_GrabInput ( SDL_GRAB_OFF );
                }
                break;
        default:
                break;
        }

        if ( _user_mode ) {
                if ( event->active.type == SDL_KEYUP ) {
                        switch ( event->key.keysym.sym ) {
                        case SDLK_l:
                                _config.next_filter_level();
                                _video->set_config ( _config );
                                break;
                        case SDLK_a:
                                _config.toggle_keep_aspect_ratio();
                                _video->set_config ( _config );
                                break;
                        default:
                                break;
                        }
                }

                // Never pass a user mode key to the application (KEYDOWN or KEYUP).
                event->active.type = SDL_NOEVENT;
        }
}

void shimmer::_process_mouse ( SDL_Event* event )
{
        DLOG ( "Process mouse..." );
        event->motion.x *= _warp_factor_x;
        event->motion.y *= _warp_factor_y;
        event->motion.xrel *= _warp_factor_x;
        event->motion.yrel *= _warp_factor_y;
}

void shimmer::_process_video_resize ( SDL_Event* event )
{
        DLOG ( "Process video resize..." );
        event->active.type = SDL_NOEVENT;
        bool do_resize = false;
        if ( _target->w != event->resize.w && event->resize.w >= 50 && event->resize.w <= 1920 ) {
                _w = event->resize.w;
                do_resize = true;
        }
        if ( _target->h != event->resize.h &&  event->resize.h >= 50 && event->resize.h <= 1080 ) {
                _h = event->resize.h;
                do_resize = true;
        }

        if ( do_resize ) {
                resize_video();
        }
}
}

