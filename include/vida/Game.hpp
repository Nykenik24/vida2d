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
  virtual void Handle(Event) = 0;

  void Quit() { want_to_quit = true; };
  bool WantToQuit() { return want_to_quit; };

private:
  bool want_to_quit;
};
} // namespace Vida
