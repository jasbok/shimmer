#include "sw_scaler.h"
#include <stdio.h>

namespace shimmer
{
template < typename T >
void sw_scaler_nn_t ( SDL_Surface * src, SDL_Surface * dest )
{
        float x_step = src->w / ( float ) dest->w;
        float y_step = src->h / ( float ) dest->h;

        T *src_ptr = ( T * ) src->pixels;
        T *dest_ptr = ( T * ) dest->pixels;

        for ( int y = 0; y < dest->h; y++ ) {
                int row = y * dest->w;
                int src_row = ( int ) ( y * y_step ) * src->w;

                for ( int x = 0; x < dest->w; x++ ) {
                        dest_ptr[row + x] = src_ptr[ ( int ) ( src_row + ( int ) ( x * x_step ) )];
                }
        }
}

void sw_scaler_nn ( SDL_Surface * src, SDL_Surface * dest, int bpp )
{
        float x_step = src->w / ( float ) dest->w;
        float y_step = src->h / ( float ) dest->h;

        Uint8 *src_ptr = ( Uint8 * ) src->pixels;
        Uint8 *dest_ptr = ( Uint8 * ) dest->pixels;

        int bytes = bpp / 8;

        for ( int y = 0; y < dest->h; y++ ) {
                int row = y * dest->w  * bytes;
                int src_row = ( int ) ( y * y_step ) * src->w * bytes;

                for ( int x = 0; x < dest->w * bytes; x++ ) {
                        dest_ptr[row + x] = src_ptr[ ( int ) ( src_row + ( int ) ( x * x_step ) )];
                }
        }
}

void sw_scaler_nn ( SDL_Surface * src, SDL_Surface * dest )
{
        if ( src->format->BitsPerPixel != dest->format->BitsPerPixel ) {
                printf ( "==> Error, source (%i) and dest (%i) BPP does not match.\n", src->format->BitsPerPixel, dest->format->BitsPerPixel );
        } else {

                switch ( src->format->BitsPerPixel ) {
                case 8:
                        sw_scaler_nn_t<Uint8> ( src, dest );
                        break;
                case 16:
                        sw_scaler_nn_t<Uint16> ( src, dest );
                        break;
                case 32:
                        sw_scaler_nn_t<Uint32> ( src, dest );
                        break;
                default:
                        printf ( "Unknown BPP: %i", src->format->BitsPerPixel );
                        sw_scaler_nn ( src, dest, src->format->BitsPerPixel );
                        break;
                }
        }
}
}
