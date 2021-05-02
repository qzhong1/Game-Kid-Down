#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderer.h"
#include "controller.h"
#include "kid.h"
#include "bar.h"
#include <vector>
#include <random>

class Game
{
private:
    
    std::vector<Normalbar> _normalbar_group;
    std::vector<Movingbar> _movingbar_group;
    std::vector<Damagebar> _damagebar_group;
    int score{0};

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_start;
    std::uniform_int_distribution<int> random_length;

    void Update();
    void BarInitiate(int w, int h);
    
public:
    Kid _kid;
    Game(int w, int h);
    void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
    int GetScore() const;

};

#endif