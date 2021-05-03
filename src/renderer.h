#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>
#include <vector>
#include "kid.h"

class Renderer
{
public:
    Renderer(int screen_width, int screen_height);
    ~Renderer();
    void draw(Kid &kid);
    
    void run(bool &running);
    void UpdateWindowTitle(int score, int frame_count);

    SDL_Rect     kid_image_position;
    SDL_Rect     damagebar_image_position;
private:

    SDL_Surface *kid_image;
    SDL_Surface *background_image;
    SDL_Surface *damagebar_image;
    SDL_Surface *movingbar_image;

    SDL_Window  *sdl_window;
    SDL_Surface *sdl_window_surface;

    SDL_Renderer *sdl_renderer;
};

#endif