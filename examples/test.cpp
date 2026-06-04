#include "vida/Engine.hpp"
#include "vida/Event.hpp"
#include "vida/Game.hpp"
#include "vida/Vector.hpp"
#include "vida/input/Key.hpp"
#include "vida/input/Mouse.hpp"
#include "vida/render/Renderer.hpp"
#include <iostream>
#include <string>

class MyGame : public Vida::Game {
public:
  bool Loop(float dt) override;
  bool Draw(Vida::Renderer *render) override;
  void Handle(Vida::Event ev) override;

private:
};

bool MyGame::Loop(float dt) { return true; }

bool MyGame::Draw(Vida::Renderer *render) { return true; }

void MyGame::Handle(Vida::Event ev) {
  switch (ev.type) {
  case Vida::EventType::KeyboardDown:
    if (ev.key == Vida::Key::Escape) {
      Quit();
    }
    break;
  case Vida::EventType::MouseDown: {
    std::string bttn = "<null>";

    switch (ev.mouse_bttn) {
    case Vida::MouseBttn::Left:
      bttn = "Pressed left";
      break;
    case Vida::MouseBttn::Right:
      bttn = "Pressed right";
      break;
    case Vida::MouseBttn::Middle:
      bttn = "Pressed scroll wheel";
      break;
    case Vida::MouseBttn::ScrollUp:
      bttn = "Scrolled up";
      break;
    case Vida::MouseBttn::ScrollDown:
      bttn = "Scrolled down";
      break;
    default:
      break;
    }

    std::cout << bttn << " at (" << ev.mx << ", " << ev.my << ")" << std::endl;
    break;
  }
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
