#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>
#include <deque>
#include "kid.h"
#include "bar.h"

constexpr std::size_t kKidHeight{40};
constexpr std::size_t kKidWidth{20};
constexpr std::size_t kBarThickness{30};

class Renderer
{
public:
    Renderer(int screen_width, int screen_height);
    ~Renderer();
    void Draw(Kid &kid);
    void SetBarHeight(std::vector<Normalbar>& normalbar, 
                      std::vector<Movingbar>& movingbar,
                      std::vector<Damagebar>& damagebar);
    void RenderBars();
    void UpdateWindowTitle(int score, int frame_count);

    SDL_Rect     kid_image_position;
    std::deque<SDL_Rect>     damagebar_image_position_group;
    std::deque<SDL_Rect>     movingbar_image_position_group;
    std::deque<SDL_Rect>     normalbar_image_position_group;
private:

    SDL_Surface *kid_image;
    SDL_Surface *background_image;
    SDL_Surface *damagebar_image;
    SDL_Surface *movingbar_image;
    SDL_Surface *normalbar_image;

    SDL_Window  *sdl_window;
    SDL_Surface *sdl_window_surface;

    SDL_Renderer *sdl_renderer;
};

#endif