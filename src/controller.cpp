#include "controller.h"

void Controller::HandleInput(bool &running, Kid &kid, Renderer &renderer){
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            running = false;
        else if (e.type == SDL_KEYDOWN){
            switch (e.key.keysym.sym){
                case SDLK_LEFT:
                renderer.kid_image_position.x -= kid._speed;
                kid._pos_x = renderer.kid_image_position.x;
                break;
                case SDLK_RIGHT:
                renderer.kid_image_position.x += kid._speed;
                kid._pos_x = renderer.kid_image_position.x;
                break;
            }
        }
    }
}    