#include "renderer.h"

Renderer::Renderer(int screen_width, int screen_height): 
        window_width(screen_width), window_height(screen_height)
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
    kid_image_position.y = 0;
    kid_image_position.w = kKidWidth;
    kid_image_position.h = kKidHeight;

    damagebar_image = IMG_Load("../img/DamagingBar.png");
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

    bloodbar_img = IMG_Load("../img/Blood.jpg");
    if(!bloodbar_img)
    {
        std::cout << "Failed to load blood bar image\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
    }
    bloodbar_img_position = {20, 20, 20, 600};

    if(TTF_Init() < 0) {
        std::cout << "Failed to initialize the TTF library\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
    }
    font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 15);
    if (font == NULL){
        std::cout << "Failed to load font\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
    }
    message1 = TTF_RenderText_Solid(font, "Press down to start the game", {111,0,255});
    message2 = TTF_RenderText_Solid(font, "Press Left and Right to move", {111,0,255});
    bloodbar_txt = TTF_RenderText_Solid(font, "Blood", {255, 0, 0});
    if (message1 == NULL || message2 == NULL || bloodbar_txt == NULL) {
        std::cout << "Failed to load message\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer(){
    SDL_FreeSurface(sdl_window_surface);
    SDL_DestroyWindow(sdl_window);
}
void Renderer::InitKidPos(Kid &kid){
    kid_image_position.x = kid._pos_x;
}

void Renderer::Draw(Kid &kid, bool wait){
    // Render background
    SDL_BlitSurface(background_image, NULL, sdl_window_surface, NULL);
    // Render instruction if game is at waiting status
    if (wait){
        SDL_Rect message_location1 = {320, 0, 200, 15};
        SDL_Rect message_location2 = {320, 15, 200, 15};
        SDL_BlitSurface(message1, NULL, sdl_window_surface, &message_location1);
        SDL_BlitSurface(message2, NULL, sdl_window_surface, &message_location2);
    }
    // Render blood bar
    SDL_Rect bloodbar_txt_location = {0, 0, 0, 0};
    SDL_BlitSurface(bloodbar_txt, NULL, sdl_window_surface, &bloodbar_txt_location);
    SDL_BlitScaled(bloodbar_img, NULL, sdl_window_surface, &bloodbar_img_position);
    //Render kid image
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
    normalbar_image_position_group.clear();
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
    movingbar_image_position_group.clear();
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
    damagebar_image_position_group.clear();
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