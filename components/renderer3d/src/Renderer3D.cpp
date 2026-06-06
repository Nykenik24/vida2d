#include "vida/renderer3d/Renderer3D.hpp"
#include "vida/core/Color.hpp"
#include "vida/core/Math.hpp"
#include "vida/core/Mesh.hpp"
#include "vida/renderer3d/Camera.hpp"
#include "vida/renderer3d/FX.hpp"
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
  LoadFX();
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

void Renderer3D::Update(float dt) { time_elapsed += dt; }

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

void Renderer3D::LoadFX() {
  auto load = [&](FX fx, const std::string &vert, const std::string &frag) {
    try {
      fx_shaders[fx] = std::make_unique<Shader>(vert, frag);
      printf("FX loaded: %s / %s\n", vert.c_str(), frag.c_str());
    } catch (const std::exception &e) {
      printf("FX failed: %s\n", e.what());
    }
  };

  load(FX::Unlit, "assets/shaders/default.vert", "assets/shaders/default.frag");
  load(FX::Lit, "assets/shaders/fx/lit.vert", "assets/shaders/fx/lit.frag");
  load(FX::Outline, "assets/shaders/fx/outline.vert",
       "assets/shaders/fx/outline.frag");
  load(FX::Transparent, "assets/shaders/fx/transparent.vert",
       "assets/shaders/fx/transparent.frag");
  load(FX::Pulse, "assets/shaders/fx/pulse.vert",
       "assets/shaders/fx/pulse.frag");
  load(FX::Dissolve, "assets/shaders/fx/dissolve.vert",
       "assets/shaders/fx/dissolve.frag");
  load(FX::Fog, "assets/shaders/fx/fog.vert", "assets/shaders/fx/fog.frag");
}

Shader &Renderer3D::GetShader(FX fx) { return *fx_shaders.at(fx); }

void Renderer3D::Clear(ColorRGBA color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer3D::Present() { glfwSwapBuffers(window.Handle()); }

void Renderer3D::SetCamera(const Camera &cam) { camera = cam; }

void Renderer3D::DrawMesh(const Mesh &mesh, const Mat4 &transform,
                          ColorRGBA color, const Texture *texture, FX fx,
                          const FXParams &fx_params) {
  const GPUMesh &gpu = GetOrUpload(mesh);

  Mat4 mvp = camera.ProjectionMatrix(window.Width(), window.Height()) *
             camera.ViewMatrix() * transform;

  Shader &shader = GetShader(fx);
  shader.Bind();
  shader.SetMat4("u_mvp", mvp);
  shader.SetMat4("u_model", transform);
  shader.SetVec3("u_color", Vec3(color.r, color.g, color.b));
  shader.SetFloat("u_time", time_elapsed);

  if (texture) {
    texture->Bind(0);
    shader.SetInt("u_texture", 0);
    shader.SetInt("u_use_texture", 1);
  } else {
    shader.SetInt("u_use_texture", 0);
  }

  if (fx == FX::Lit) {
    shader.SetVec3("u_light_dir", glm::normalize(fx_params.light_dir));
    shader.SetVec3("u_light_color", fx_params.light_color);
    shader.SetFloat("u_ambient", fx_params.ambient);
  }

  if (fx == FX::Outline) {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    Mat4 outline_transform =
        transform * glm::scale(Mat4(1.0f), Vec3(fx_params.outline_width));
    Mat4 outline_mvp =
        camera.ProjectionMatrix(window.Width(), window.Height()) *
        camera.ViewMatrix() * outline_transform;
    shader.SetMat4("u_mvp", outline_mvp);
    shader.SetVec3("u_color",
                   Vec3(fx_params.outline_color.r, fx_params.outline_color.g,
                        fx_params.outline_color.b));
    glBindVertexArray(gpu.VAO);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)gpu.vertex_count);

    glCullFace(GL_BACK);
    shader.SetMat4("u_mvp", mvp);
    shader.SetVec3("u_color", Vec3(color.r, color.g, color.b));
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)gpu.vertex_count);
    glDisable(GL_CULL_FACE);
    glBindVertexArray(0);
    return;
  }

  if (fx == FX::Transparent) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader.SetFloat("u_alpha", fx_params.alpha);
  }

  if (fx == FX::Pulse)
    shader.SetFloat("u_pulse_speed", fx_params.pulse_speed);

  if (fx == FX::Dissolve)
    shader.SetFloat("u_dissolve_speed", fx_params.dissolve_speed);

  if (fx == FX::Fog) {
    shader.SetVec3("u_fog_color",
                   Vec3(fx_params.fog_color.r, fx_params.fog_color.g,
                        fx_params.fog_color.b));
    shader.SetFloat("u_fog_near", fx_params.fog_near);
    shader.SetFloat("u_fog_far", fx_params.fog_far);
  }
  glBindVertexArray(gpu.VAO);
  glDrawArrays(GL_TRIANGLES, 0, (GLsizei)gpu.vertex_count);
  glBindVertexArray(0);

  if (fx == FX::Transparent)
    glDisable(GL_BLEND);

  if (texture)
    texture->Unbind();
}

void Renderer3D::DrawCube(Vec3 position, Vec3 size, const Texture &texture,
                          ColorRGBA tint, FX fx, const FXParams &fx_params) {
  static const Mesh mesh = Mesh::Cube();
  Mat4 transform =
      glm::translate(Mat4(1.0f), position) * glm::scale(Mat4(1.0f), size);
  DrawMesh(mesh, transform, tint, &texture, fx, fx_params);
}

void Renderer3D::DrawCube(Vec3 position, Vec3 size, ColorRGBA color, FX fx,
                          const FXParams &fx_params) {
  static const Mesh mesh = Mesh::Cube();
  Mat4 transform =
      glm::translate(Mat4(1.0f), position) * glm::scale(Mat4(1.0f), size);
  DrawMesh(mesh, transform, color, nullptr, fx, fx_params);
}

void Renderer3D::DrawQuad(Vec2 position, Vec2 size, const Texture &texture,
                          ColorRGBA tint, FX fx, const FXParams &fx_params) {
  static const Mesh mesh = Mesh::Quad();
  Mat4 transform = glm::translate(Mat4(1.0f), Vec3(position, 0.0f)) *
                   glm::scale(Mat4(1.0f), Vec3(size, 1.0f));
  DrawMesh(mesh, transform, tint, &texture, fx, fx_params);
}

void Renderer3D::DrawQuad(Vec2 position, Vec2 size, ColorRGBA color, FX fx,
                          const FXParams &fx_params) {
  static const Mesh mesh = Mesh::Quad();
  Mat4 transform = glm::translate(Mat4(1.0f), Vec3(position, 0.0f)) *
                   glm::scale(Mat4(1.0f), Vec3(size, 1.0f));
  DrawMesh(mesh, transform, color, nullptr, fx, fx_params);
}

void Renderer3D::DrawSphere(Vec3 position, float radius, const Texture &texture,
                            ColorRGBA tint, FX fx, const FXParams &fx_params) {
  static const Mesh mesh = Mesh::Sphere(16, 16);
  Mat4 transform = glm::translate(Mat4(1.0f), position) *
                   glm::scale(Mat4(1.0f), Vec3(radius * 2.0f));
  DrawMesh(mesh, transform, tint, &texture, fx, fx_params);
}

void Renderer3D::DrawSphere(Vec3 position, float radius, ColorRGBA color, FX fx,
                            const FXParams &fx_params) {
  static const Mesh mesh = Mesh::Sphere(16, 16);
  Mat4 transform = glm::translate(Mat4(1.0f), position) *
                   glm::scale(Mat4(1.0f), Vec3(radius * 2.0f));
  DrawMesh(mesh, transform, color, nullptr, fx, fx_params);
}

void Renderer3D::DrawCone(Vec3 position, float radius, float height,
                          const Texture &texture, ColorRGBA tint, FX fx,
                          const FXParams &fx_params) {
  static const Mesh mesh = Mesh::Cone(32);
  Mat4 transform =
      glm::translate(Mat4(1.0f), position) *
      glm::scale(Mat4(1.0f), Vec3(radius * 2.0f, height, radius * 2.0f));
  DrawMesh(mesh, transform, tint, &texture, fx, fx_params);
}

void Renderer3D::DrawCone(Vec3 position, float radius, float height,
                          ColorRGBA color, FX fx, const FXParams &fx_params) {
  static const Mesh mesh = Mesh::Cone(32);
  Mat4 transform =
      glm::translate(Mat4(1.0f), position) *
      glm::scale(Mat4(1.0f), Vec3(radius * 2.0f, height, radius * 2.0f));
  DrawMesh(mesh, transform, color, nullptr, fx, fx_params);
}

void Renderer3D::DrawPyramid(Vec3 position, Vec3 size, const Texture &texture,
                             ColorRGBA tint, FX fx, const FXParams &fx_params) {
  static const Mesh mesh = Mesh::Pyramid();
  Mat4 transform =
      glm::translate(Mat4(1.0f), position) * glm::scale(Mat4(1.0f), size);
  DrawMesh(mesh, transform, tint, &texture, fx, fx_params);
}

void Renderer3D::DrawPyramid(Vec3 position, Vec3 size, ColorRGBA color, FX fx,
                             const FXParams &fx_params) {
  static const Mesh mesh = Mesh::Pyramid();
  Mat4 transform =
      glm::translate(Mat4(1.0f), position) * glm::scale(Mat4(1.0f), size);
  DrawMesh(mesh, transform, color, nullptr, fx, fx_params);
}
} // namespace Vida
