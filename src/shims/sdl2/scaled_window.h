#ifndef SCALED_WINDOW_H
#define SCALED_WINDOW_H

#include <SDL.h>

class Scaled_Window{
public:
    
    Scaled_Window ();
    Scaled_Window (SDL_Window* window);
    Scaled_Window (SDL_Window* window, SDL_Renderer* renderer);
    
    ~Scaled_Window();
    
    void window(SDL_Window* window);
    SDL_Window* window();
    
    void source_window(SDL_Window* window);
    SDL_Window* source_window();
    
    void renderer(SDL_Renderer* renderer);
    SDL_Renderer* renderer();
    
    void source_renderer(SDL_Renderer* renderer);
    SDL_Renderer* source_renderer();
    
    void render();
    
private:
    SDL_Window* _window;
    const char* _window_title;
    SDL_Renderer* _renderer;
    SDL_RendererInfo _renderer_info;
    SDL_Texture* _texture;
    SDL_Surface* _surface;
    
    SDL_Window* _src_window;
    SDL_Renderer* _src_renderer;
};

#endif
