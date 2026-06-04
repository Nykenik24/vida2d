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

  virtual bool Loop() = 0;
  virtual bool Draw(Renderer *renderer) = 0;
  virtual void Handle(Event) = 0;

  void Quit() { want_to_quit = true; };
  bool WantToQuit() { return want_to_quit; };

  Vector2f GetWindowSize() {
    return Vector2f(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
  };

  float dt;

private:
  bool want_to_quit;
};
} // namespace Vida
