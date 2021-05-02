#include "game.h"

Game::Game(int w, int h)
    : _kid(w, h),
      engine(dev()),
      random_start(0, static_cast<int>(w - 1)),
      random_length(0, static_cast<int>(h - 1)) {
  // BarInitiate(w, h);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  renderer.InitKid(_kid);

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, _kid, renderer);
    Update();
    renderer.Render(_kid, _normalbar_group, _movingbar_group, _damagebar_group);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
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

void Game::Update(){
  if (!_kid._alive)
      return;

  
}

int Game::GetScore() const {

}

void Game::BarInitiate(int w, int h){
  // Ten normal bars with random start position and length
  for(int i = 0; i <10; i++){
    float start_pos = random_start(engine);
    float length = random_length(engine);
    _normalbar_group.emplace_back(std::move(Normalbar(length, start_pos)));
  }

  // Ten Moving bars with random start position and length
  // Two different speeds
  for(int i = 0; i <5; i++){
    float start_pos = random_start(engine);
    float length = random_length(engine);
    _movingbar_group.emplace_back(std::move(Movingbar(length, start_pos, 1)));
  }
  for(int i = 0; i <5; i++){
    float start_pos = random_start(engine);
    float length = random_length(engine);
    _movingbar_group.emplace_back(std::move(Movingbar(length, start_pos, 2)));
  }

  // Ten damaging bars, two types of damage per second
  for(int i = 0; i <5; i++){
    float start_pos = random_start(engine);
    float length = random_length(engine);
    _damagebar_group.emplace_back(std::move(Damagebar(length, start_pos, 1)));
  }
  for(int i = 0; i <5; i++){
    float start_pos = random_start(engine);
    float length = random_length(engine);
    _damagebar_group.emplace_back(std::move(Damagebar(length, start_pos, 2)));
  }
}