#include "vida/render/Renderer.hpp"

namespace Vida {
Renderer::Renderer(std::string title, Vector2 size) {
  static bool initialized = false;
  if (!initialized) {
    int argc = 0;
    glutInit(&argc, nullptr);
    initialized = true;
  }
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(static_cast<int>(size.x), static_cast<int>(size.y));
  windowId = glutCreateWindow(title.c_str());

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glutDisplayFunc([] {});

  glutCloseFunc([] { Renderer::shouldClose = true; });
}

Renderer::~Renderer() {
  if (windowId != 0)
    glutDestroyWindow(windowId);
}

void Renderer::BeginFrame() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EndFrame() {
  glutSwapBuffers();
  glutMainLoopEvent();
}
} // namespace Vida
