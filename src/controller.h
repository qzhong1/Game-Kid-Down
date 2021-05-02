#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "kid.h"
#include "bar.h"
#include "SDL.h"
#include "renderer.h"

class Controller
{
private:
    
public:
    void HandleInput(bool &running, Kid &kid, Renderer &renderer) const;
};

#endif