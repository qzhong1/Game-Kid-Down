#include "renderer.h"

Renderer::Renderer(int screen_width, int screen_height)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
    }

    sdl_window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width, 
                                screen_height, 0);
    if(!sdl_window)
    {
        std::cout << "Failed to create window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
    }

    sdl_window_surface = SDL_GetWindowSurface(sdl_window);
    if(!sdl_window_surface)
    {
        std::cout << "Failed to get the surface from the window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
    }

    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_WEBP);
    background_image = IMG_Load("../img/Background.jpg");
    if(!background_image)
    {
        std::cout << "Failed to load background image\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
    }

    kid_image = IMG_Load("../img/stickman.webp");
    if(!kid_image)
    {
        std::cout << "Failed to load kid image\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
    }
    kid_image_position.x = 320;
    kid_image_position.y = 0;
    kid_image_position.w = 32;
    kid_image_position.h = 55;

    damagebar_image = IMG_Load("../img/Damagingbar.png");
    if(!damagebar_image)
    {
        std::cout << "Failed to load damagebar image\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
    }
    damagebar_image_position.x = 250;
    damagebar_image_position.y = 320;
    damagebar_image_position.w = 200;
    damagebar_image_position.h = 55;
}

Renderer::~Renderer(){
    SDL_FreeSurface(sdl_window_surface);
    SDL_DestroyWindow(sdl_window);
}

void Renderer::draw(Kid &kid){
    
    SDL_BlitSurface(background_image, NULL, sdl_window_surface, NULL);
    SDL_BlitScaled(damagebar_image, NULL, sdl_window_surface, &damagebar_image_position);
    SDL_BlitScaled(kid_image, NULL, sdl_window_surface, &kid_image_position);
    SDL_UpdateWindowSurface(sdl_window);
    
}

void UpdateWindowTitle(int score, int frame_count){

}