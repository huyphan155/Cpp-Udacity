#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake) const;
  bool IsPaused() const;
  void TogglePaused() const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
   mutable bool paused{false};  // variable to track pause state
};

#endif