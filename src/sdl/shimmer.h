#ifndef SHIMMER_H
#define SHIMMER_H

#include "video_surface.h"
#include <SDL.h>

class shimmer
{
public:
        enum class UPDATE_SCHEME
        {
                SDL_FLIP, GL_SWAPBUFFERS, FIXED_RATE, ANY
        };

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
        UPDATE_SCHEME update_scheme();
        void update_scheme ( UPDATE_SCHEME scheme );


private:
        //
        //  CONFIGURATIONS
        //
        int _w, _h, _bpp;
        Uint32 _video_flags;
        bool _use_software;
        int _update_rate;

        //
        //  VIDEO
        //
        video_surface *_video;
        SDL_Surface *_source, *_target;
        UPDATE_SCHEME _update_scheme;

        //
        //  INPUT
        //
        float _warp_factor_x, _warp_factor_y;

        //
        //  PROCESS FLOW
        //
        bool _do_resize;
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
        void _process_mouse(SDL_Event* event);
        void _process_keyboard(SDL_Event* event);
        void _process_video_resize(SDL_Event* event);
        
        //
        //  DEBUG
        //
        void _print_out_configuration();
};

#endif
