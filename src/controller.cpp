#include "controller.h"

void Controller::HandleInput(bool &running, Kid &kid, Renderer &renderer){
    // Controll kid movement during game
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            running = false;
        else if (e.type == SDL_KEYDOWN){
            switch (e.key.keysym.sym){
                case SDLK_LEFT:
                    if (renderer.kid_image_position.x > 0) {
                        renderer.kid_image_position.x -= kid._speed;
                        kid._pos_x = renderer.kid_image_position.x;
                    }
                    break;
                case SDLK_RIGHT:
                    if (renderer.kid_image_position.x + kKidWidth < renderer.window_width) {
                        renderer.kid_image_position.x += kid._speed;
                        kid._pos_x = renderer.kid_image_position.x;
                    }
                    break;
            }
        }
    }
}    

void Controller::StartGame(bool &wait, Kid &kid, Renderer &renderer, bool &running){
    // controll kid movement before game starts
    while (SDL_PollEvent(&check)) {
        if (check.type == SDL_KEYDOWN)
            switch (check.key.keysym.sym)
            {
            case SDLK_DOWN: // start game
                wait = false;
                break;
            case SDLK_LEFT:
                    if (renderer.kid_image_position.x > 0) {
                        renderer.kid_image_position.x -= kid._speed;
                        kid._pos_x = renderer.kid_image_position.x;
                    }
                    break;
                case SDLK_RIGHT:
                    if (renderer.kid_image_position.x + kKidWidth < renderer.window_width) {
                        renderer.kid_image_position.x += kid._speed;
                        kid._pos_x = renderer.kid_image_position.x;
                    }
                    break;
            }
        else if (check.type == SDL_QUIT) {
            // exist both loops in game.run if user choose quit
            wait = false;
            running = false;
        }
    }
}

void Controller::EndFinal(bool &running, Kid &kid, bool &wait, Renderer &renderer, int &score){
    // control game behaviour after game over
    while (SDL_PollEvent(&click)) {
        if (click.type == SDL_QUIT) 
            running = false;
        else if(click.type == SDL_MOUSEBUTTONDOWN){
            if (click.button.button == SDL_BUTTON_LEFT){
                int x, y;
                SDL_GetMouseState(&x, &y); 
                // Check if user clicks on restart
                if (x>280 && x<360 && y>280 && y<360){
                    // Initialise sorce and everything for kid
                    kid._alive = true;
                    wait = true;
                    renderer.kid_image_position = {320, 0, kKidWidth, kKidHeight};
                    renderer.bloodbar_img_position.h = 600;
                    kid._pos_y = 0;
                    kid._pos_x = 320;
                    kid.ResetBlood();
                    renderer.ResetScore(score);
                }
            }
        }
            
    }
}