#pragma once

#include "GL/freeglut_std.h"
#include "vida/Event.hpp"
#include "vida/Game.hpp"
#include "vida/input/KeyMap.hpp"
#include "vida/input/Mouse.hpp"
#include <chrono>
#include <memory>
#include <type_traits>

namespace Vida {
class Engine {
public:
  template <typename T> static Engine Create() {
    static_assert(std::is_base_of_v<Game, T>,
                  "Engine requires a Game-derived class.");
    Engine engine(std::make_unique<T>());
    return engine;
  }
  Engine(Engine &&) = default;
  Engine(const Engine &) = delete;
  Engine &operator=(Engine &&) = default;
  Engine &operator=(const Engine &) = delete;
  ~Engine() = default;

  bool Update();
  bool Running() { return running; };
  void Quit();

  int Run();

  void SetWindowTitle(std::string title);
  void SetWindowSize(Vector2f size);
  void SetWindowPos(Vector2f pos);

private:
private:
  inline static Engine *s_instance = nullptr;

  void InitInputHandling() {
    s_instance = this;

    glutKeyboardFunc([](unsigned char k, int, int) {
      if (auto key = KeyFromGlut(k))
        s_instance->game->Handle(Event(EventType::KeyboardDown, *key));
    });

    glutKeyboardUpFunc([](unsigned char k, int, int) {
      if (auto key = KeyFromGlut(k))
        s_instance->game->Handle(Event(EventType::KeyboardUp, *key));
    });

    glutSpecialFunc([](int k, int, int) {
      if (auto key = KeyFromGlutSpecial(k))
        s_instance->game->Handle(Event(EventType::KeyboardDown, *key));
    });

    glutSpecialUpFunc([](int k, int, int) {
      if (auto key = KeyFromGlutSpecial(k))
        s_instance->game->Handle(Event(EventType::KeyboardUp, *key));
    });

    glutMouseFunc([](int b, int state, int x, int y) {
      if (auto bttn = MouseButtonFromGlut(b))
        s_instance->game->Handle(Event(state == GLUT_DOWN ? EventType::MouseDown
                                                          : EventType::MouseUp,
                                       *bttn, x, y));
    });

    glutMotionFunc([](int x, int y) {
      Event ev(EventType::MouseDragged);
      ev.mx = x, ev.my = y;
      s_instance->game->Handle(ev);
    });

    glutPassiveMotionFunc([](int x, int y) {
      Event ev(EventType::MouseMoved);
      ev.mx = x, ev.my = y;
      s_instance->game->Handle(ev);
    });
  }

  explicit Engine(std::unique_ptr<Game> g)
      : game(std::move(g)), renderer("Vida2D", Vector2f(800, 600)) {
    prev = std::chrono::high_resolution_clock::now();
    InitInputHandling();
  }

  std::unique_ptr<Game> game;
  bool running = true;
  float dt;
  std::chrono::time_point<std::chrono::high_resolution_clock> prev;

  bool first_loop = true;
  bool first_draw = true;

  // WARN: MUST BE DECLARED LAST!!!!!
  Renderer renderer;
};
} // namespace Vida
