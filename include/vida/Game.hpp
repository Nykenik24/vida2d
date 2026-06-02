#pragma once

#include "vida/Event.hpp"
#include "vida/render/Renderer.hpp"
#include <GL/freeglut.h>

namespace Vida {
class Game {
public:
  Game() = default;
  Game(Game &&) = default;
  Game(const Game &) = default;
  Game &operator=(Game &&) = default;
  Game &operator=(const Game &) = default;
  virtual ~Game() = default;

  virtual bool Loop(float) = 0;
  virtual bool Draw(Renderer *renderer) = 0;
  virtual void Handle(EventType) = 0;

private:
};
} // namespace Vida
