#ifndef SHIMMER_H
#define SHIMMER_H

#include "config.h"
#include "video_surface.h"
#include <SDL.h>
#include <thread>

namespace shimmer
{
class shimmer
{
public:
        shimmer();
        ~shimmer();

        //
        //  CONFIGURATION AND RESOURCE MANAGEMENT
        //
        void init();
        void destroy();

        //
        //  VIDEO
        //
        void setup_video();
        void update_video();
        void update_video ( int numrects, SDL_Rect* rects );
        void refresh_video();
        void resize_video();

        //
        //  INPUT
        //
        void process_event ( SDL_Event *event );
        void warp_coord ( int *x, int *y );
        void warp_coord ( Uint16 *x, Uint16 *y );

        //
        //  FIELD ACCESS
        //
        SDL_Surface* source();
        void source ( SDL_Surface *source );
        SDL_Surface* target();


private:
        //
        //  CONFIGURATIONS
        //
        int _w, _h, _bpp;
        Uint32 _video_flags;
        config _config;

        //
        //  VIDEO
        //
        video_surface *_video;
        SDL_Surface *_source, *_target;

        //
        //  INPUT
        //
        float _warp_factor_x, _warp_factor_y;

        //
        //  PROCESS FLOW
        //
        bool _user_mode;

private:
        //
        //  VIDEO
        //
        void _configure_video_from_source();
        void _create_video_surface();

        //
        // INPUT
        //
        void _calculate_warp_factor();
        void _process_mouse ( SDL_Event* event );
        void _process_keyboard ( SDL_Event* event );
        void _process_video_resize ( SDL_Event* event );

        //
        //  DEBUG
        //
        void _print_out_configuration();
};
}

#endif
