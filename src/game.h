#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderer.h"
#include "controller.h"
#include "kid.h"
#include "bar.h"
#include <vector>
#include <deque>
#include <random>

class Game
{
private:
    // Generated initally for random pick at run time
    std::vector<Normalbar> _normalbar_group_source;
    std::vector<Movingbar> _movingbar_group_source;
    std::vector<Damagebar> _damagebar_group_source;
    // Picked randomly from source, show at run time
    std::deque<Normalbar> _normalbar_group_present;
    std::deque<Movingbar> _movingbar_group_present;
    std::deque<Damagebar> _damagebar_group_present; 

    int score{0};

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_start;
    std::uniform_int_distribution<int> random_length;

    void Update(Renderer &renderer);
    void BarInitiate();
    void PickNewBar(float height);

public:
    Kid _kid;
    Game(int w, int h);
    void Run(Controller &controller, Renderer &renderer,
           std::size_t target_frame_duration);
    
    int GetScore() const;

};

#endif