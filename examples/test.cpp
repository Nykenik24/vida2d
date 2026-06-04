#include "vida/Engine.hpp"
#include "vida/Event.hpp"
#include "vida/Game.hpp"
#include "vida/Vector.hpp"
#include "vida/input/Key.hpp"
#include "vida/render/Renderer.hpp"
#include <iostream>
#include <string>

int wrap(int n, int min, int max) {
  if (n < min)
    return min;
  if (n > max)
    return max;
  return n;
};

class MyGame : public Vida::Game {
public:
  bool Loop() override;
  bool Draw(Vida::Renderer *render) override;
  void Handle(Vida::Event ev) override;
  void Move(int dx, int dy) {
    x += (speed * dx) * dt;
    y += (speed * dy) * dt;
  }

  int x = 50, y = 50;
  const int speed = 1500;

private:
};

bool MyGame::Loop() {
  Vida::Vector2f window_size = GetWindowSize();
  x = wrap(x, 0, window_size.x);
  y = wrap(y, 0, window_size.y);
  return true;
}

bool MyGame::Draw(Vida::Renderer *render) {
  render->DrawFillRect(Vida::Vector2f(x, y), Vida::Vector2f(50, 50));
  return true;
}

void MyGame::Handle(Vida::Event ev) {
  switch (ev.type) {
  case Vida::EventType::KeyboardDown:
    switch (ev.key) {
    case Vida::Key::Escape:
      Quit();
      break;
    case Vida::Key::w:
      std::cout << "Up" << std::endl;
      Move(0, -1);
      break;
    case Vida::Key::a:
      std::cout << "Left" << std::endl;
      Move(-1, 0);
      break;
    case Vida::Key::s:
      std::cout << "Down" << std::endl;
      Move(0, 1);
      break;
    case Vida::Key::d:
      std::cout << "Right" << std::endl;
      Move(1, 0);
      break;
    default:
      break;
    }
    break;
  default:
    return;
  }
}

int main(void) {
  auto engine = Vida::Engine::Create<MyGame>();
  engine.SetWindowTitle("My cool game");
  engine.SetWindowSize(Vida::Vector2f(1080, 720));

  return engine.Run();
}
