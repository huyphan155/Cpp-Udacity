#include "renderer.h"
#include "game.h"
#include <iostream>
#include <string>
#include <SDL_image.h>  // Include SDL_image for image loading

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      sdl_window(nullptr, SDL_DestroyWindow){
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window.reset(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN));

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Load background image as texture
  background_texture = LoadTexture("./../image/number0.jpeg");
}

Renderer::~Renderer() {
  SDL_DestroyTexture(background_texture);  // Free the background texture
  SDL_Quit();
}

// Load texture from file
SDL_Texture* Renderer::LoadTexture(const std::string& path) {
  SDL_Surface* surface = IMG_Load(path.c_str());
  if (!surface) {
    std::cerr << "Unable to load image " << path << "\n";
    return nullptr;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);

  return texture;
}

// Render the background image
void Renderer::RenderBackground() {
  // Render the background texture
  SDL_RenderCopy(sdl_renderer, background_texture, NULL, NULL);
}

void Renderer::Render(Snake const snake, SDL_Point const &food, SDL_Point const &special_food, const Game& game) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render the background
  RenderBackground();

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render Special food evey 5 regular foods
  if (game.GetCountSpecial() >= 5) {
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);  // Red color
  block.x = special_food.x * block.w;
  block.y = special_food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window.get(), title.c_str());
}
