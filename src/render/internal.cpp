// clang-format off
#include <GL/glew.h>
// clang-format on
#include "GL/freeglut_std.h"
#include "vida/Color.hpp"
#include "vida/Vector.hpp"
#include "vida/render/Renderer.hpp"
#include <cstdlib>

static const char *VERT_SRC = R"glsl(
  #version 330 core
  layout(location = 0) in vec2 pos;
  void main() {
    gl_Position = vec4(pos, 0.0, 1.0);
  }
)glsl";

static const char *FRAG_SRC = R"glsl(
  #version 330 core
  uniform vec4 uColor;
  out vec4 fragColor;
  void main() {
    fragColor = uColor;
  }
)glsl";

static GLuint CompileShader(GLenum type, const char *src) {
  GLuint s = glCreateShader(type);
  glShaderSource(s, 1, &src, nullptr);
  glCompileShader(s);
  GLint ok;
  glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
  if (!ok) {
    char log[512];
    glGetShaderInfoLog(s, 512, nullptr, log);
    fprintf(stderr, "Shader error: %s\n", log);
  }
  return s;
}

namespace Vida {
void Renderer::InitShaders() {
  GLuint vert = CompileShader(GL_VERTEX_SHADER, VERT_SRC);
  GLuint frag = CompileShader(GL_FRAGMENT_SHADER, FRAG_SRC);
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vert);
  glAttachShader(shaderProgram, frag);
  glLinkProgram(shaderProgram);
  glDeleteShader(vert);
  glDeleteShader(frag);

  colorUniformLoc = glGetUniformLocation(shaderProgram, "uColor");

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}

void Renderer::BeginFrame() {
  int w = glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  window_size = Vector2f(w, h);

  glViewport(0, 0, static_cast<GLsizei>(window_size.x),
             static_cast<GLsizei>(window_size.y));
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EndFrame() {
  glutSwapBuffers();
  glutMainLoopEvent();
}

Vector2f Renderer::PixelToNDC(Vector2f p) const {
  return {(p.x / window_size.x) * 2.0f - 1.0f,
          -((p.y / window_size.y) * 2.0f - 1.0f)};
}

void Renderer::DrawPrimitive(GLenum mode, const std::vector<float> &verts,
                             ColorRGBA color) {
  glUseProgram(shaderProgram);
  glUniform4f(colorUniformLoc, color.r / 255.0f, color.g / 255.0f,
              color.b / 255.0f, color.a / 255.0f);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  size_t byteSize = verts.size() * sizeof(float);
  if (byteSize > vboCapacity) {
    glBufferData(GL_ARRAY_BUFFER, byteSize, verts.data(), GL_DYNAMIC_DRAW);
    vboCapacity = byteSize;
  } else {
    glBufferSubData(GL_ARRAY_BUFFER, 0, byteSize, verts.data());
  }

  glDrawArrays(mode, 0, static_cast<GLsizei>(verts.size() / 2));
  glBindVertexArray(0);
}
} // namespace Vida
