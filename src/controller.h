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
    void HandleInput(bool &running, Kid &kid, Renderer &renderer);
};

#endif