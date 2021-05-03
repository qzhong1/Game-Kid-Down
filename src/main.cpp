#include <iostream>
#include "renderer.h"
#include "game.h"
#include "controller.h"

int main()
{   constexpr std::size_t kScreenWidth{640};
    constexpr std::size_t kScreenHeight{800};

    bool running = true;
    Renderer renderer(kScreenWidth, kScreenHeight);
    Controller controller;
    Game game(kScreenWidth, kScreenHeight);
    game.Run(controller, renderer, 15);

}