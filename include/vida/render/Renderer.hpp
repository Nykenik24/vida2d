#pragma once

#include "vida/Vector.hpp"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <string>

namespace Vida {

class Renderer {
public:
  Renderer(std::string title, Vector2 size);
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  Renderer(Renderer &&) = default;
  Renderer &operator=(Renderer &&) = default;
  ~Renderer();

  void BeginFrame();
  void EndFrame();
  bool ShouldClose() const { return shouldClose; }

private:
  int windowId = 0;
  static inline bool shouldClose = false;
};

} // namespace Vida
