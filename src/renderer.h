#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <deque>
#include <string>
#include "kid.h"
#include "bar.h"

constexpr std::size_t kBarThickness{20};

class Renderer
{
public:
    Renderer(int screen_width, int screen_height);
    ~Renderer();
    void Draw(bool wait, int score);
    void InitKidPos(Kid &kid);
    void SetBarHeight(std::deque<Normalbar>& normalbar, 
                      std::deque<Movingbar>& movingbar,
                      std::deque<Damagebar>& damagebar);
    void RenderBars();
    void DrawFinal(int score); // Display scene after game ends

    int window_width;
    int window_height;

    SDL_Rect                 kid_image_position;
    SDL_Rect                 bloodbar_img_position;
    std::deque<SDL_Rect>     damagebar_image_position_group;
    std::deque<SDL_Rect>     movingbar_image_position_group;
    std::deque<SDL_Rect>     normalbar_image_position_group;
private:
    SDL_Surface     *message1;
    SDL_Surface     *message2;
    SDL_Surface     *ending_msg1;
    SDL_Rect        ending_msg1_pos{0, 0, 200, 100};
    SDL_Surface     *ending_msg2;
    SDL_Rect        ending_msg2_pos{0, 40, 200, 100};
    SDL_Surface     *score_text;
    SDL_Surface     *bloodbar_txt;
    SDL_Surface     *bloodbar_img;
    SDL_Surface     *kid_image;
    SDL_Surface     *background_image;
    SDL_Surface     *damagebar_image;
    SDL_Surface     *movingbar_image;
    SDL_Surface     *normalbar_image;

    SDL_Window      *sdl_window;
    SDL_Surface     *sdl_window_surface;

    TTF_Font        *font;
    TTF_Font        *ending_font;
};

#endif