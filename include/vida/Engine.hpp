#pragma once

#include "vida/Game.hpp"
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

private:
  explicit Engine(std::unique_ptr<Game> g)
      : game(std::move(g)), renderer("Vida2D", Vector2(800, 600)) {
    prev = std::chrono::high_resolution_clock::now();
  }

  std::unique_ptr<Game> game;
  bool running = true;
  float dt;
  std::chrono::time_point<std::chrono::high_resolution_clock> prev;

  // WARN: MUST BE DECLARED LAST!!!!!
  Renderer renderer;

  friend class Renderer;
};
} // namespace Vida
