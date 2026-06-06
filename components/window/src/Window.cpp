#include "vida/window/Window.hpp"
#include "GLFW/glfw3.h"
#include <stdexcept>

namespace Vida {
Window::Window(int width, int height, const char *title)
    : width(width), height(height) {
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!handle) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(handle);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw std::runtime_error("Failed to initialize GLAD");

  glfwSetWindowUserPointer(handle, this);
  glfwSetFramebufferSizeCallback(handle, OnResize);
}

Window::~Window() {
  glfwDestroyWindow(handle);
  glfwTerminate();
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(handle); }

void Window::PollEvents() { glfwPollEvents(); }

void Window::OnResize(GLFWwindow *window, int width, int height) {
  auto *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
  self->width = width;
  self->height = height;
  glViewport(0, 0, width, height);
}
} // namespace Vida
