#include "scaled_window.h"

#include <stdio.h>

Scaled_Window::Scaled_Window()
{
}


Scaled_Window::Scaled_Window ( SDL_Window* window_a )
{
        window ( window_a );
}

Scaled_Window::Scaled_Window ( SDL_Window* window_a, SDL_Renderer* renderer_a )
{
        window ( window_a );
        renderer ( renderer_a );
}

Scaled_Window::~Scaled_Window()
{
    if ( _texture ) {
                SDL_DestroyTexture ( _texture );
    }
}

void Scaled_Window::window ( SDL_Window* window )
{
        _window = window;
        _window_title = SDL_GetWindowTitle ( window );
        printf ( "[%s] Creating scaled window...\n", _window_title );
}

SDL_Window * Scaled_Window::window()
{

        return _window;
}

void Scaled_Window::source_window ( SDL_Window* window )
{
        _src_window = window;
}

SDL_Window * Scaled_Window::source_window()
{
        return _src_window;
}

void Scaled_Window::renderer ( SDL_Renderer* renderer )
{
        _renderer = renderer;
        SDL_GetRendererInfo ( renderer, &_renderer_info );
        printf ( "[%s] Setting window renderer: %s\n", _window_title, _renderer_info.name );
}

SDL_Renderer * Scaled_Window::renderer()
{
        return _renderer;
}

void Scaled_Window::source_renderer ( SDL_Renderer* renderer )
{
        _src_renderer = renderer;
}

SDL_Renderer * Scaled_Window::source_renderer()
{
        return _src_renderer;
}

void Scaled_Window::render ()
{
//         if ( _texture ) {
//                 SDL_DestroyTexture ( _texture );
//         }
// 
//         if ( _src_window ) {
//                 SDL_Surface* window_surface = SDL_GetWindowSurface ( _src_window );
// 
//                 if ( window_surface ) {
//                         _texture = SDL_CreateTextureFromSurface ( _renderer, window_surface );
//                         
//                         if ( _texture ) {
//                             SDL_RenderCopy ( _renderer, _texture, NULL, NULL );
//                         }
//                         else{
//                             printf ( "[%s] Texture is null.\n", _window_title );
//                         }
//                         
//                 } else {
//                         printf ( "[%s] Window surface is null.\n", _window_title );
//                 }
//         } else {
//                 printf ( "[%s] Source window is null.\n", _window_title );
//         }
    int w,h;
    SDL_GetWindowSize(_src_window, &w, &h);
    static SDL_Surface* _surface = SDL_CreateRGBSurface(0, w,h, 32, 0, 0, 0, 0);    
    SDL_RenderReadPixels(_src_renderer, NULL, _surface->format->format, _surface->pixels, _surface->pitch);
    _texture = SDL_CreateTextureFromSurface(_renderer, _surface);
    
    SDL_RenderCopy(_renderer, _texture, NULL, NULL);
    SDL_DestroyTexture(_texture);
    //SDL_FreeSurface(_surface);
}
