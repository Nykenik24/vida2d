#include "vida/renderer3d/Renderer3D.hpp"
#include "vida/core/Color.hpp"
#include "vida/core/Math.hpp"
#include "vida/core/Mesh.hpp"
#include "vida/renderer3d/Camera.hpp"
#include "vida/texture/Texture.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

Renderer3D::Renderer3D(Window &window) : window(window) {
  InitBuffers();
  default_shader = std::make_unique<Shader>("assets/shaders/default.vert",
                                            "assets/shaders/default.frag");
}

void Renderer3D::SetShader(std::unique_ptr<Shader> shader) {
  default_shader = std::move(shader);
}

void Renderer3D::ResetShader() {
  default_shader = std::make_unique<Shader>("assets/shaders/default.vert",
                                            "assets/shaders/default.frag");
}

Renderer3D::~Renderer3D() {
  for (auto &[key, gpu] : mesh_cache) {
    glDeleteVertexArrays(1, &gpu.VAO);
    glDeleteBuffers(1, &gpu.VBO);
  }
  glDeleteProgram(default_shader->Handle());

  camera.position = Vec3(0.0f, 0.0f, 5.0f);
  camera.target = Vec3(0.0f, 0.0f, 0.0f);
  camera.fov = 45.0f;
  camera.orthographic = false;
}

void Renderer3D::InitBuffers() {
  glEnable(GL_DEPTH_TEST);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, uv));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, normal));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);
}

void Renderer3D::Clear(ColorRGBA color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer3D::Present() { glfwSwapBuffers(window.Handle()); }

void Renderer3D::SetCamera(const Camera &cam) { camera = cam; }

void Renderer3D::DrawMesh(const Mesh &mesh, const Mat4 &transform,
                          ColorRGBA color, const Texture *texture) {
  const GPUMesh &gpu = GetOrUpload(mesh);

  Mat4 mvp = camera.ProjectionMatrix(window.Width(), window.Height()) *
             camera.ViewMatrix() * transform;

  default_shader->Bind();
  default_shader->SetMat4("u_mvp", mvp);
  default_shader->SetVec3("u_color", Vec3(color.r, color.g, color.b));

  if (texture) {
    texture->Bind(0);
    default_shader->SetInt("u_texture", 0);
    default_shader->SetInt("u_use_texture", 1);
  } else {
    default_shader->SetInt("u_use_texture", 0);
  }

  glBindVertexArray(gpu.VAO);
  glDrawArrays(GL_TRIANGLES, 0, (GLsizei)gpu.vertex_count);
  glBindVertexArray(0);

  if (texture)
    texture->Unbind();
}

void Renderer3D::DrawCube(Vec3 position, Vec3 size, const Texture &texture,
                          ColorRGBA tint) {
  static const Mesh mesh = Mesh::Cube();
  Mat4 transform =
      glm::translate(Mat4(1.0f), position) * glm::scale(Mat4(1.0f), size);
  DrawMesh(mesh, transform, tint, &texture);
}

void Renderer3D::DrawCube(Vec3 position, Vec3 size, ColorRGBA color) {
  static const Mesh mesh = Mesh::Cube();

  Mat4 transform =
      glm::translate(Mat4(1.0f), position) * glm::scale(Mat4(1.0f), size);

  DrawMesh(mesh, transform, color);
}

void Renderer3D::DrawQuad(Vec2 position, Vec2 size, const Texture &texture,
                          ColorRGBA tint) {
  static const Mesh mesh = Mesh::Quad();
  Mat4 transform = glm::translate(Mat4(1.0f), Vec3(position, 0.0f)) *
                   glm::scale(Mat4(1.0f), Vec3(size, 1.0f));
  DrawMesh(mesh, transform, tint, &texture);
}

void Renderer3D::DrawQuad(Vec2 position, Vec2 size, ColorRGBA color) {
  static const Mesh mesh = Mesh::Quad();

  Mat4 transform = glm::translate(Mat4(1.0f), Vec3(position, 0.0f)) *
                   glm::scale(Mat4(1.0f), Vec3(size, 1.0f));

  DrawMesh(mesh, transform, color);
}

void Renderer3D::DrawSphere(Vec3 position, float radius, const Texture &texture,
                            ColorRGBA tint) {
  static const Mesh mesh = Mesh::Sphere(16, 16);

  Mat4 transform = glm::translate(Mat4(1.0f), position) *
                   glm::scale(Mat4(1.0f), Vec3(radius * 2.0f));

  DrawMesh(mesh, transform, tint, &texture);
}

void Renderer3D::DrawSphere(Vec3 position, float radius, ColorRGBA color) {
  static const Mesh mesh = Mesh::Sphere(16, 16);

  Mat4 transform = glm::translate(Mat4(1.0f), position) *
                   glm::scale(Mat4(1.0f), Vec3(radius * 2.0f));

  DrawMesh(mesh, transform, color);
}

void Renderer3D::DrawCone(Vec3 position, float radius, float height,
                          const Texture &texture, ColorRGBA tint) {
  static const Mesh mesh = Mesh::Cone(32);

  Mat4 transform =
      glm::translate(Mat4(1.0f), position) *
      glm::scale(Mat4(1.0f), Vec3(radius * 2.0f, height, radius * 2.0f));

  DrawMesh(mesh, transform, tint, &texture);
}

void Renderer3D::DrawCone(Vec3 position, float radius, float height,
                          ColorRGBA color) {
  static const Mesh mesh = Mesh::Cone(32);

  Mat4 transform =
      glm::translate(Mat4(1.0f), position) *
      glm::scale(Mat4(1.0f), Vec3(radius * 2.0f, height, radius * 2.0f));

  DrawMesh(mesh, transform, color);
}

void Renderer3D::DrawPyramid(Vec3 position, Vec3 size, const Texture &texture,
                             ColorRGBA tint) {
  static const Mesh mesh = Mesh::Pyramid();

  Mat4 transform =
      glm::translate(Mat4(1.0f), position) * glm::scale(Mat4(1.0f), size);

  DrawMesh(mesh, transform, tint, &texture);
}

void Renderer3D::DrawPyramid(Vec3 position, Vec3 size, ColorRGBA color) {
  static const Mesh mesh = Mesh::Pyramid();

  Mat4 transform =
      glm::translate(Mat4(1.0f), position) * glm::scale(Mat4(1.0f), size);

  DrawMesh(mesh, transform, color);
}
} // namespace Vida
