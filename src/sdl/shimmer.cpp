#include "shimmer.h"
#include "sdl_shim.h"

namespace shimmer
{
shimmer::shimmer()
        : _video ( nullptr ),
          _source ( nullptr ),
          _target ( nullptr ),
          _warp_factor_x ( 1 ),
          _warp_factor_y ( 1 ),
          _opengl_initialised ( false ),
          _user_mode ( false )
{
        glewExperimental = true;
}

shimmer::~shimmer()
{
        if ( _video ) delete _video;
        if ( _shader_manager ) delete _shader_manager;
}

//
// VIDEO
//
void shimmer::init_opengl()
{
        glewInit();
        _shader_manager = new shader_manager ();
        _opengl_initialised = true;
        _setup_menus();
}

void shimmer::setup_video()
{
        _create_video_surface();

        if ( !_opengl_initialised ) {
                init_opengl();
        }

        if ( _video ) delete _video;
        _video = new hw_surface ( _source, _target,  _shader_manager->create_program ( {config::instance().vertex_shader}, {config::instance().fragment_shader} ) );
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
        _create_video_surface();
        if ( _video )
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
        if ( x ) *x = *x * _warp_factor_x;
        if ( y ) *y = *y * _warp_factor_y;
}

void shimmer::warp_coord ( Uint16* x, Uint16* y )
{
        if ( x ) *x = *x * _warp_factor_x;
        if ( y ) *y = *y * _warp_factor_y;
}

//
// FIELD ACCESS
//
SDL_Surface *shimmer::source()
{
        return _source;
}

void shimmer::source ( SDL_Surface* source )
{
        _source = source;
}

SDL_Surface *shimmer::target()
{
        return _target;
}

//
//  PRIVATE: VIDEO
//
void shimmer::_create_video_surface()
{
        if ( config::instance().width == 0 && config::instance().height == 0 ) {
                config::instance().width = _source->w;
                config::instance().height = _source->h;
        } else {
                // Do not allow the window to resize into nothing.
                config::instance().width = config::instance().width > 50 ? config::instance().width : 50;
                config::instance().height = config::instance().height > 50 ? config::instance().height: 50;
        }

        _target = sym::SDL_SetVideoMode ( config::instance().width, config::instance().height, 32, SDL_RESIZABLE | SDL_OPENGL );
        _calculate_warp_factor();
}

//
// PRIVATE: INPUT
//
void shimmer::_calculate_warp_factor()
{
        if ( _source && _target ) {
                _warp_factor_x = _source->w / ( float ) ( _target->w );
                _warp_factor_y = _source->h / ( float ) ( _target->h );
        }
}

void shimmer::shimmer::_setup_menus()
{
        menu<std::string, menu_item<std::string, std::string>> fs_menu;
        for ( auto fs : _shader_manager->fs_shaders() ) {
                fs_menu.push_back ( menu_item<std::string, std::string> ( fs, fs, [this] ( menu_item<std::string, std::string>& item ) {
                        config::instance().fragment_shader = item.value();
                        if(_video) _video->shader_program(_shader_manager->create_program ( {config::instance().vertex_shader}, {config::instance().fragment_shader} ));
                        return true;
                } ) );
        }
        _menu_system.insert ( MENUS::FRAGMENT_SHADER_SELECTION, fs_menu );
}

}




