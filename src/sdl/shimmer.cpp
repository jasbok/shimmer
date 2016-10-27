#include "shimmer.h"
#include "sdl_shim.h"

#include "sw_surface.h"
#include "hw_surface.h"

shimmer::shimmer()
        : _w ( 0 ), _h ( 0 ), _bpp ( 32 ),
          _video_flags ( 0 ),
          _use_software ( false ),

          _video ( nullptr ),
          _source ( nullptr ), _target ( nullptr ),
          _update_scheme ( UPDATE_SCHEME::SDL_FLIP ),

          _warp_factor_x ( 1 ), _warp_factor_y ( 1 ),

          _do_resize ( false ),
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
        _print_out_configuration();
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
        _configure_video_from_source();
        _create_video_surface();
        
        if(_video) delete _video;
        
        if ( _use_software ) {
                _video = new sw_surface ( _source, _target );
        } else {
                _video = new hw_surface ( _source, _target );
        }
}

void shimmer::update_video()
{
        if ( _do_resize ) {
                resize_video();
        }
        _video->update();
}

void shimmer::resize_video()
{
        DLOG ( "Resizing video..." );
        _create_video_surface();
        _do_resize = false;
}


//
// INPUT
//
void shimmer::process_event ( SDL_Event* event )
{
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
        DLOG ( "Setting source... %p", source );
        _source = source;
}

SDL_Surface * shimmer::target()
{
        //DLOG ( "Getting target... %p", _target );
        return _target;
}

shimmer::UPDATE_SCHEME shimmer::update_scheme()
{
        DLOG ( "Setting update scheme..." );
        return _update_scheme;
}

void shimmer::update_scheme ( shimmer::UPDATE_SCHEME scheme )
{
        DLOG ( "Getting update scheme..." );
        _update_scheme = scheme;
}

//
//  PRIVATE: VIDEO
//
void shimmer::_configure_video_from_source()
{
        DLOG ( "Configure video from source..." );
        
        if(!_w) _w = _source->w;
        if(!_h) _h = _source->h;

        if ( _use_software ) {
                _bpp = _source->format->BitsPerPixel;
                _video_flags = _source->flags | SDL_RESIZABLE;
        }
}

void shimmer::_create_video_surface()
{
        DLOG ( "Create video surface..." );
        if ( _use_software ) {
                DLOG ( "Created software surface." );
                _target = sdl::SDL_SetVideoMode ( _w, _h, _bpp, _video_flags );
        } else {
                DLOG ( "Created hardware surface." );
                _target = sdl::SDL_SetVideoMode ( _w, _h, _bpp, _video_flags | SDL_RESIZABLE | SDL_OPENGL );
        }

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
                if ( event->active.type == SDL_KEYDOWN ) {
                        _user_mode = !_user_mode;
                        sdl::SDL_WM_GrabInput ( _user_mode == false ? SDL_GRAB_ON : SDL_GRAB_OFF );
                }

                // Never pass a user mode key to the application (KEYDOWN or KEYUP).
                event->active.type = SDL_NOEVENT;
                break;
        default:
                break;
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
        if ( _target->w != event->resize.w && event->resize.w >= 50 && event->resize.w <= 1920 ) {
                _w = event->resize.w;
                _do_resize = true;
        }
        if ( _target->h != event->resize.h &&  event->resize.h >= 50 && event->resize.h <= 1080 ) {
                _h = event->resize.h;
                _do_resize = true;
        }
}

void shimmer::_print_out_configuration()
{
        printf ( "Shimmer Configuration:\n" );
        printf ( "======================\n" );
        printf ( "Target Resolution: %ux%ux%u\n", _w, _h, _bpp );
        printf ( "Use Software Scaler: %u\n", _use_software );
}

