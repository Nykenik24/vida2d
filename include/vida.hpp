#pragma once

#include "vida/event.hpp"
#include <chrono>
#include <memory>
#include <type_traits>
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
  virtual bool Draw() = 0;
  virtual void Handle(EventType) = 0;

private:
};

class Engine {
public:
  template <typename T> static Engine Create() {
    static_assert(std::is_base_of_v<Game, T>,
                  "Engine requires a Game-derived class.");
    return Engine(std::make_unique<T>());
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
  explicit Engine(std::unique_ptr<Game> g) : game(std::move(g)) {
    prev = std::chrono::high_resolution_clock::now();
  }

  std::unique_ptr<Game> game;
  bool running;
  float dt;
  std::chrono::time_point<std::chrono::high_resolution_clock> prev;
};
} // namespace Vida
