#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "kid.h"
#include "bar.h"
#include <vector>

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();
  void UpdateKidPosition(Kid &kid);
  void Render(Kid &kid, std::vector<Normalbar> normal_bar,
              std::vector<Movingbar> moving_bar, std::vector<Damagebar> damage_bar);
  void UpdateWindowTitle(int score, int frame_count);
  void InitKid(Kid &kid);

 private:
  SDL_Window    *sdl_window;
  SDL_Surface   *sdl_window_surface;
  SDL_Renderer  *sdl_renderer;
  SDL_Surface   *kid_image;
  SDL_Texture   *kid_texture;
  SDL_Rect      kid_image_position;
  SDL_Surface   *background_image;
  SDL_Texture   *background_texture;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};


#endif