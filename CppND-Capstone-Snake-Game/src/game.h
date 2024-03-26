#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "LogStore.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  int GetCountSpecial() const;
  int GetTotalSpecial() const;

 private:
  Snake snake;
  SDL_Point food;
  SDL_Point special_food; // Special Food item
  LogStore logStore; // Log store 

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int countSpecial{0};

  void PlaceSpecial();
  void PlaceFood();
  void Update();
};

#endif