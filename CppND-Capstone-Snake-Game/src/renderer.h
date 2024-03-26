#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <string>
#include <memory> //header for std::unique_ptr

// Forward declaration of the Game class
class Game;

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, SDL_Point const &special_food, const Game& game);
  void UpdateWindowTitle(int score, int fps);

 private:
  std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> sdl_window; // smart poiter used
  SDL_Renderer *sdl_renderer;
  SDL_Texture *background_texture;  // variable for background texture

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  // Load texture from file
  SDL_Texture* LoadTexture(const std::string& path);
  // Render the background image
  void RenderBackground();
};

#endif
