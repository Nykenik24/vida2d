#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Vida {
class Window {
public:
  Window(int width, int height, const char *title);
  ~Window();

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  bool ShouldClose() const;
  void PollEvents();

  int Width() const { return width; }
  int Height() const { return height; }

  GLFWwindow *Handle() const { return handle; }

private:
  GLFWwindow *handle;
  int width, height;

  static void OnResize(GLFWwindow *window, int width, int height);
};
} // namespace Vida
