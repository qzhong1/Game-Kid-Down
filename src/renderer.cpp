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
    kid_image_position.w = kKidWidth;
    kid_image_position.h = kKidHeight;

    damagebar_image = IMG_Load("../img/Damagingbar.png");
    if(!damagebar_image)
    {
        std::cout << "Failed to load damagebar image\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
    }
    movingbar_image = IMG_Load("../img/MovingBar.png");
    if(!movingbar_image)
    {
        std::cout << "Failed to load movingbar image\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
    }
    normalbar_image = IMG_Load("../img/NormalBar.jpg");
    if(!normalbar_image)
    {
        std::cout << "Failed to load normalbar image\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer(){
    SDL_FreeSurface(sdl_window_surface);
    SDL_DestroyWindow(sdl_window);
}

void Renderer::Draw(Kid &kid){
    
    SDL_BlitSurface(background_image, NULL, sdl_window_surface, NULL);
    SDL_BlitScaled(kid_image, NULL, sdl_window_surface, &kid_image_position);

    // Render bars
    for(auto position : normalbar_image_position_group){
        SDL_BlitScaled(normalbar_image, NULL, sdl_window_surface, &position);
    }
    for(auto position : movingbar_image_position_group){
        SDL_BlitScaled(movingbar_image, NULL, sdl_window_surface, &position);
    }
    for(auto position : damagebar_image_position_group){
        SDL_BlitScaled(damagebar_image, NULL, sdl_window_surface, &position);
    }
    SDL_UpdateWindowSurface(sdl_window);
}

void Renderer::SetBarHeight(std::deque<Normalbar>& normalbar, 
                            std::deque<Movingbar>& movingbar, 
                            std::deque<Damagebar>& damagebar){
    // Set bars height according to locations in game.cpp
    SDL_Rect normalbar_image_position;
    normalbar_image_position.h = kBarThickness;
    if (!normalbar.empty()){
        for (auto bar : normalbar){
            normalbar_image_position.x = bar.GetStartPos();
            normalbar_image_position.y = bar.GetCurrentHeight();
            normalbar_image_position.w = bar.GetLength();
            normalbar_image_position_group.emplace_back(normalbar_image_position);
        }
    }
    
    SDL_Rect movingbar_image_position;
    movingbar_image_position.h = kBarThickness;
    if (!movingbar.empty()){
        for (auto bar : movingbar){
            movingbar_image_position.x = bar.GetStartPos();
            movingbar_image_position.y = bar.GetCurrentHeight();
            movingbar_image_position.w = bar.GetLength();
            movingbar_image_position_group.emplace_back(movingbar_image_position);
        }
    }
    

    SDL_Rect damagebar_image_position;
    damagebar_image_position.h = kBarThickness;
    if (!damagebar.empty()){
        for (auto bar : damagebar){
            damagebar_image_position.x = bar.GetStartPos();
            damagebar_image_position.y = bar.GetCurrentHeight();
            damagebar_image_position.w = bar.GetLength();
            damagebar_image_position_group.emplace_back(damagebar_image_position);
        }
    }
    
}

void UpdateWindowTitle(int score, int frame_count){

}