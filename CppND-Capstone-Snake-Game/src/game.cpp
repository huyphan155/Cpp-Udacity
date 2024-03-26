#include "game.h"
#include <iostream>
#include "SDL.h"
#include <thread>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      countSpecial(0) {
  PlaceFood();
  PlaceSpecial();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  
  // Run LogStore as a separate thread
  std::thread logStoreThread(&LogStore::LogSpecialItem, &logStore);

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    // Check if the game is paused
    if (controller.IsPaused() != true) {
    // Update the game only when it's not paused
      Update();
    }
    renderer.Render(snake, food, special_food, *this);

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
  // Join the LogStore thread when the main loop exits
  logStoreThread.join();
  
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      PlaceSpecial();
      return;
    }
  }
}

void Game::PlaceSpecial() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // Special.
    if (!snake.SnakeCell(x, y)) {
      special_food.x = x;
      special_food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  // cordinate to check food
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // cordinate to check special
  int Special_new_x = static_cast<int>(snake.head_x);
  int Special_new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    // increase count special , Special food appears every 5 regular foods 
    countSpecial++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

  if ( countSpecial >= 5)
  {
    // Check if there's Special over here
    if (special_food.x == Special_new_x && special_food.y == Special_new_y) {
      // double score for special food
      score += 2;
      PlaceSpecial();
      // mark as 1 consumtion of a special
      logStore.LogSpecialItem();
      // snake don't grow and decrease speed.
      snake.speed -= 0.02;
      // reset countSpecial
      countSpecial = 0;
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
int Game::GetCountSpecial() const { return countSpecial; }
int Game::GetTotalSpecial() const { return logStore.GetSpecialItemCount(); }