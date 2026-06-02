#include "vida.hpp"
#include "vida/event.hpp"
#include <iostream>

class MyGame : public Vida::Game {
public:
  bool Loop(float dt) override;
  bool Draw() override { return true; };
  void Handle(Vida::EventType ev) override;

private:
};

bool MyGame::Loop(float dt) {
  std::cout << dt << std::endl;
  return true;
}

void MyGame::Handle(Vida::EventType ev) {
  switch (ev) {
  default:
    std::cout << "Event!" << std::endl;
  }
}

int main(void) {
  auto engine = Vida::Engine::Create<MyGame>();
  while (engine.Running()) {
    engine.Update();
  }
}
