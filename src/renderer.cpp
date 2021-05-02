#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Kid Down", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);
  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  sdl_window_surface = SDL_GetWindowSurface(sdl_window);
  if (sdl_window_surface == nullptr) {
    std::cerr << "Failed to get window surface.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_WEBP);
  // Set background picture
  background_image = IMG_Load("../img/Background.jpg");
  if (nullptr == background_image){
    std::cerr << "Background image not loaded" << "\n";
  }
  background_texture = SDL_CreateTextureFromSurface(sdl_renderer, background_image);
  SDL_RenderCopy(sdl_renderer, background_texture, NULL, NULL);
  SDL_RenderPresent(sdl_renderer);
}

Renderer::~Renderer() {
    SDL_DestroyTexture(kid_texture);
    SDL_FreeSurface(kid_image);
	  SDL_DestroyRenderer(sdl_renderer);  
    SDL_DestroyWindow(sdl_window);
    SDL_FreeSurface(sdl_window_surface);

    SDL_Quit();
}

void Renderer::InitKid(Kid &kid){
  //Load stick man as kid to be controlled by user
  kid_image = IMG_Load("../img/stickman.webp");
  if (nullptr == kid_image){
    std::cerr << "Kid image not loaded" << "\n";
  }
  kid_texture = SDL_CreateTextureFromSurface(sdl_renderer, kid_image);

  // Control kid size
  kid_image_position = {320, 320, 32, 64};
  SDL_RenderCopy(sdl_renderer, kid_texture, NULL, &kid_image_position);
  SDL_RenderPresent(sdl_renderer);
  
  kid._pos_x = kid_image_position.x;
  kid._pos_y = kid_image_position.y;
}

void Renderer::UpdateKidPosition(Kid &kid){
  kid_image_position.x = kid._pos_x;
  kid_image_position.y = kid._pos_y;
  
  SDL_BlitSurface(kid_image, NULL, sdl_window_surface, NULL);
  SDL_UpdateWindowSurface(sdl_window);

  // SDL_RenderCopy(sdl_renderer, kid_texture, NULL, &kid_image_position);
  // SDL_RenderPresent(sdl_renderer);
  std::cout<<kid_image_position.x<<std::endl;
}

void Renderer::Render(Kid &kid, std::vector<Normalbar> normal_bar,
      std::vector<Movingbar> moving_bar, std::vector<Damagebar> damage_bar){
  

}

void Renderer::UpdateWindowTitle(int score, int frame_count) {
  std::string title{"Kid Down: "};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}