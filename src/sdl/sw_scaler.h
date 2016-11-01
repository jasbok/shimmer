#ifndef SCALE_H
#define SCALE_H

#include <SDL.h>

namespace shimmer
{
void sw_scaler_nn ( SDL_Surface * src, SDL_Surface * dest, int bpp );
void sw_scaler_nn ( SDL_Surface * src, SDL_Surface * dest );
}

#endif
