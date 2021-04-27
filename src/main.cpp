#include <iostream>
#include "renderer.h"

int main() {
    constexpr std::size_t kScreenWidth{640};
    constexpr std::size_t kScreenHeight{1280};
    constexpr std::size_t kGridWidth{32};
    constexpr std::size_t kGridHeight{32};

    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    
    return 0;
}