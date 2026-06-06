#include "vida/renderer3d/Renderer3D.hpp"
#include "vida/core/Color.hpp"
#include "vida/core/Math.hpp"
#include "vida/renderer3d/Camera.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>

namespace Vida {

Mat4 Camera::ViewMatrix() const {
  return glm::lookAt(position, target, Vec3(0.0f, 1.0f, 0.0f));
}

Mat4 Camera::ProjectionMatrix(int width, int height) const {
  if (orthographic) {
    return glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.1f, 100.0f);
  }
  float aspect = (float)width / (float)height;
  return glm::perspective(glm::radians(fov), aspect, 0.1f, 1000.0f);
}

static const char *VERT_SRC = R"(
    #version 330 core
    layout(location = 0) in vec3 a_pos;

    uniform mat4 u_mvp;

    void main() {
        gl_Position = u_mvp * vec4(a_pos, 1.0);
    }
)";

static const char *FRAG_SRC = R"(
    #version 330 core
    out vec4 frag_color;

    uniform vec3 u_color;

    void main() {
        frag_color = vec4(u_color, 1.0);
    }
)";

static GLuint CompileShader(GLenum type, const char *src) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  int ok;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
  if (!ok) {
    char log[512];
    glGetShaderInfoLog(shader, 512, nullptr, log);
    throw std::runtime_error(std::string("Shader compile error: ") + log);
  }

  return shader;
}

Renderer3D::Renderer3D(Window &window) : window(window) {
  InitShaders();
  InitBuffers();
}

Renderer3D::~Renderer3D() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shader_program);

  camera.position = Vec3(0.0f, 0.0f, 5.0f);
  camera.target = Vec3(0.0f, 0.0f, 0.0f);
  camera.fov = 45.0f;
  camera.orthographic = false;
}

void Renderer3D::InitShaders() {
  GLuint vert = CompileShader(GL_VERTEX_SHADER, VERT_SRC);
  GLuint frag = CompileShader(GL_FRAGMENT_SHADER, FRAG_SRC);

  shader_program = glCreateProgram();
  glAttachShader(shader_program, vert);
  glAttachShader(shader_program, frag);
  glLinkProgram(shader_program);

  int ok;
  glGetProgramiv(shader_program, GL_LINK_STATUS, &ok);
  if (!ok) {
    char log[512];
    glGetProgramInfoLog(shader_program, 512, nullptr, log);
    throw std::runtime_error(std::string("Shader link error: ") + log);
  }

  glDeleteShader(vert);
  glDeleteShader(frag);
}

void Renderer3D::InitBuffers() {
  glEnable(GL_DEPTH_TEST);

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

void Renderer3D::Clear(ColorRGBA color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer3D::Present() { glfwSwapBuffers(window.Handle()); }

void Renderer3D::SetCamera(const Camera &cam) { camera = cam; }

void Renderer3D::DrawMesh(const Vec3 *vertices, size_t count,
                          const Mat4 &transform, ColorRGBA color) {
  Mat4 mvp = camera.ProjectionMatrix(window.Width(), window.Height()) *
             camera.ViewMatrix() * transform;

  glUseProgram(shader_program);
  glUniformMatrix4fv(glGetUniformLocation(shader_program, "u_mvp"), 1, GL_FALSE,
                     glm::value_ptr(mvp));
  glUniform3fv(glGetUniformLocation(shader_program, "u_color"), 1,
               glm::value_ptr(Vec3(color.r, color.g, color.b)));

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vec3), vertices,
               GL_DYNAMIC_DRAW);

  glDrawArrays(GL_TRIANGLES, 0, (GLsizei)count);
  glBindVertexArray(0);
}

void Renderer3D::DrawCube(Vec3 position, Vec3 size, ColorRGBA color) {
  float hx = size.x * 0.5f;
  float hy = size.y * 0.5f;
  float hz = size.z * 0.5f;

  Vec3 vertices[] = {
      {-hx, -hy, hz},  {hx, -hy, hz},   {hx, hy, hz},    {hx, hy, hz},
      {-hx, hy, hz},   {-hx, -hy, hz},  {hx, -hy, -hz},  {-hx, -hy, -hz},
      {-hx, hy, -hz},  {-hx, hy, -hz},  {hx, hy, -hz},   {hx, -hy, -hz},
      {-hx, -hy, -hz}, {-hx, -hy, hz},  {-hx, hy, hz},   {-hx, hy, hz},
      {-hx, hy, -hz},  {-hx, -hy, -hz}, {hx, -hy, hz},   {hx, -hy, -hz},
      {hx, hy, -hz},   {hx, hy, -hz},   {hx, hy, hz},    {hx, -hy, hz},
      {-hx, hy, hz},   {hx, hy, hz},    {hx, hy, -hz},   {hx, hy, -hz},
      {-hx, hy, -hz},  {-hx, hy, hz},   {-hx, -hy, -hz}, {hx, -hy, -hz},
      {hx, -hy, hz},   {hx, -hy, hz},   {-hx, -hy, hz},  {-hx, -hy, -hz},
  };

  Mat4 transform = glm::translate(Mat4(1.0f), position);
  DrawMesh(vertices, 36, transform, color);
}

void Renderer3D::DrawQuad(Vec2 position, Vec2 size, ColorRGBA color) {
  float hx = size.x * 0.5f;
  float hy = size.y * 0.5f;
  float x = position.x;
  float y = position.y;

  Vec3 vertices[] = {
      {x - hx, y - hy, 0.0f}, {x + hx, y - hy, 0.0f}, {x + hx, y + hy, 0.0f},
      {x + hx, y + hy, 0.0f}, {x - hx, y + hy, 0.0f}, {x - hx, y - hy, 0.0f},
  };

  Mat4 transform = Mat4(1.0f);
  DrawMesh(vertices, 6, transform, color);
}

} // namespace Vida
