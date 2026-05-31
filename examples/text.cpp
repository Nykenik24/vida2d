#include "vida2d/render/text.hpp"
#include "SDL3/SDL_stdinc.h"
#include "vida2d.hpp"
#include "vida2d/color.hpp"
#include "vida2d/render/render.hpp"
#include "vida2d/time/time.hpp"
#include "vida2d/vec.hpp"
#include <iostream>
#include <unistd.h>

Vida2D::Color RandomColor() {
  static const Vida2D::Color colors[] = {
      Vida2D::White,
      Vida2D::Red,
      Vida2D::Green,
      Vida2D::Blue,
      Vida2D::Color(128, 0, 128, 255), // Purple
      Vida2D::Color(255, 255, 0, 255), // Yellow
  };
  return colors[SDL_rand(6)];
}

int main(void) {
  Vida2D::Context::Init("test", 800, 600);

  Vida2D::Render::SetBackgroundColor(Vida2D::Color(20, 20, 20, 255));

  Vida2D::Render::Font font("assets/font.ttf", 24);
  Vida2D::Render::Text label(font, "Hello, World!", Vida2D::Red);

  double timer = 0;
  Vida2D::Vector2 pos(0, 0);

  while (Vida2D::Running()) {
    Vida2D::PollEvents();
    Vida2D::ClearScreen();

    Vida2D::Render::SetColor(Vida2D::White);
    if (!label.Draw(pos)) {
      std::cout << "couldn't render text!" << std::endl;
    }

    timer += Vida2D::Time::GetDelta();
    if (timer >= 1) {
      label.SetColor(RandomColor());
      auto size = SDL_rand(96);
      font.SetSize(size >= 12 ? size : 12);
      pos = Vida2D::Vector2(SDL_rand(800), SDL_rand(600));
      timer = 0;
    }

    Vida2D::Render::Update();
    Vida2D::Update();
  }
}
