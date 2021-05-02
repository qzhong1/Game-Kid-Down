#include "controller.h"
#include <iostream>

void Controller::HandleInput(bool &running, Kid &kid, Renderer &renderer) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_LEFT:
          kid._direction = kLeft;
          std::cout <<"left"<<std::endl;
          kid.UpdatePosition();
          renderer.UpdateKidPosition(kid);
          break;

        case SDLK_RIGHT:
          kid._direction = kRight;
          std::cout <<"right"<<std::endl;
          kid.UpdatePosition();
          renderer.UpdateKidPosition(kid);
          break;
      }
    }
  }
}