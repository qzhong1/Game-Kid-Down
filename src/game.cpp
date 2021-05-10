#include "game.h"
#include "bar.h"
#include <iostream>
Game::Game(int w, int h)
    :_kid(w, h), engine(dev()), window_height(h), window_width(w),
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
    bool wait = true;

    renderer.InitKidPos(_kid);
    
    while (running) {
        frame_start = SDL_GetTicks();
        
        // Input, Update, Render - the main game loop
        controller.HandleInput(running, _kid, renderer);
        // Update bar image height
        renderer.SetBarHeight(_normalbar_group_present, _movingbar_group_present, _damagebar_group_present);
        ReplaceBar();
        renderer.Draw(_kid, wait, score);
        Update(renderer, running);
        frame_end = SDL_GetTicks();
        // Hold the game before user press down key
        while(wait) {
            controller.StartGame(wait, _kid, renderer);
            renderer.Draw(_kid, wait, score);
        }
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

void Game::Update(Renderer &renderer, bool &running){
    if (!_kid._alive)
        return;
    if (_kid._pos_y >= window_height || _kid._pos_y < 0 || renderer.bloodbar_img_position.h <= 0){
        _kid._alive = false;
        running = false;
        return;
    }
    _kid.FallOnBar(_normalbar_group_present, _movingbar_group_present, _damagebar_group_present);
    if (_kid.GetOnBar()) {
        _kid._pos_y -= kBarHeightIncrement;
        if (_kid.GetBarType() == damaging) {
            if (renderer.bloodbar_img_position.h > 0){
                renderer.bloodbar_img_position.h -= kBloodDecrement;
                _kid.ReduceBlood();
            }
        }
        if (_kid.GetBarType() == moving) {
            if (renderer.kid_image_position.x > 0) {
                renderer.kid_image_position.x -= kCarouselSpeed;
                _kid.MoveOnCarousel();
            }
        }
    }
    renderer.kid_image_position.y = _kid._pos_y;

    // Update bar height
    if (!_normalbar_group_present.empty()) {
        for(auto &bar : _normalbar_group_present) {
            bar.IncreaseHeight(); 
        }
    }
        
    if (!_movingbar_group_present.empty()) {
        for(auto &bar : _movingbar_group_present) {
            bar.IncreaseHeight(); 
        }
    }
        
    if (!_damagebar_group_present.empty()) {
        for(auto &bar : _damagebar_group_present) {
            bar.IncreaseHeight(); 
        }
    }
        
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

void Game::ReplaceBar() {
    // Add new bar if height of the last bar is more than 60 from window buttom
    if (_normalbar_group_present.back().GetCurrentHeight() < window_height - 60 &&
    _movingbar_group_present.back().GetCurrentHeight() < window_height - 60 &&
    _damagebar_group_present.back().GetCurrentHeight() < window_height - 60 ){
        PickNewBar(window_height);
        score += 1;
    }
    if (!_normalbar_group_present.empty()) {
        if (_normalbar_group_present.front().GetCurrentHeight() <= 0){
            _normalbar_group_present.pop_front();
        }
    }
    if (!_movingbar_group_present.empty()) {
        if (_movingbar_group_present.front().GetCurrentHeight() <= 0){
            _movingbar_group_present.pop_front();
        }
    }
    if (!_damagebar_group_present.empty()) {
        if (_damagebar_group_present.front().GetCurrentHeight() <= 0){
            _damagebar_group_present.pop_front();
        }
    }
    
}