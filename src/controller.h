#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "kid.h"
#include "bar.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderer.h"

class Controller
{
private:
    
public:
    SDL_Event e;
    SDL_Event check;
    SDL_Event click;
    void HandleInput(bool &running, Kid &kid, Renderer &renderer);
    void StartGame(bool &wait, Kid &kid, Renderer &renderer, bool &running);
    void EndFinal(bool &running, Kid &kid, bool &wait, Renderer &renderer, int &score);
};

#endif