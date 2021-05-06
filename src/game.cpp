#include "game.h"

Game::Game(int w, int h)
    :_kid(w, h), engine(dev()), 
    random_start(0, static_cast<int>(w * 4/5)),
    random_length(static_cast<int>(w / 5), static_cast<int>(w / 3))
{
    BarInitiate();
}

void Game::Run(Controller &controller, Renderer &renderer, 
                std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    renderer.InitKidPos(_kid);
    
    while (running) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop
        controller.HandleInput(running, _kid, renderer);
        Update(renderer);
        renderer.SetBarHeight(_normalbar_group_present, _movingbar_group_present, _damagebar_group_present);
        renderer.Draw(_kid);
        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle takes
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }

    }
}

void Game::Update(Renderer &renderer){
    if (!_kid._alive)
        return;
    _kid.FallOnBar(_normalbar_group_present, _movingbar_group_present, _damagebar_group_present);
    renderer.kid_image_position.y = _kid._pos_y;
}

int Game::GetScore() const {

}

void Game::BarInitiate(){
    // Construct the source to pick from
    for(int i = 0; i <10; i++){
        float start_pos = random_start(engine);
        float length = random_length(engine);
        Normalbar normalbar(length, start_pos);
        _normalbar_group_source.emplace_back(normalbar);
    }
    for(int i = 0; i <5; i++){
        float start_pos = random_start(engine);
        float length = random_length(engine);
        Movingbar movingbar(length, start_pos);
        _movingbar_group_source.emplace_back(movingbar);
    }
    for(int i = 0; i <5; i++){
        float start_pos = random_start(engine);
        float length = random_length(engine);
        Damagebar damagebar(length, start_pos);
        _damagebar_group_source.emplace_back(damagebar);
    }
    // Pick 10 bars from the source for initial frame
    for (int i = 0; i <10; i++){
        PickNewBar(i*60+60);

        // Get the x position of the first bar to set kid initial position
        float init_kid_x;
        if (i == 0) {
            if (!_normalbar_group_present.empty())
                init_kid_x = (_normalbar_group_present[0].GetStartPos() + 
                              _normalbar_group_present[0].GetEndPos()) / 2;
            if (!_damagebar_group_present.empty())
                init_kid_x = (_damagebar_group_present[0].GetStartPos() + 
                              _damagebar_group_present[0].GetEndPos()) / 2;
            if (!_movingbar_group_present.empty())
                init_kid_x = (_movingbar_group_present[0].GetStartPos() + 
                              _movingbar_group_present[0].GetEndPos()) / 2;
        }
        _kid._pos_x = init_kid_x;
    }
}

void Game::PickNewBar(float height){
    // Pick a bar to show at random from the 3 types of sources
    std::uniform_int_distribution<int> rand_index(0, 19);
    int bar_index = rand_index(engine);
    if (bar_index<10){
        _normalbar_group_source[bar_index].SetCurrentHeight(height);
        _normalbar_group_present.emplace_back(_normalbar_group_source[bar_index]);
        }
    else if (bar_index >= 10 && bar_index <15){
        _movingbar_group_source[bar_index-10].SetCurrentHeight(height);
        _movingbar_group_present.emplace_back(_movingbar_group_source[bar_index-10]);
        }
    else if (bar_index >=15){
        _damagebar_group_source[bar_index-15].SetCurrentHeight(height);
        _damagebar_group_present.emplace_back(_damagebar_group_source[bar_index-15]);
        }
}