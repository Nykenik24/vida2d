#pragma once

#include "vida/core/Color.hpp"
#include "vida/core/Mesh.hpp"
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include "vida/core/Math.hpp"
#include "vida/renderer3d/Camera.hpp"
#include "vida/renderer3d/Shader.hpp"
#include "vida/window/Window.hpp"
#include <memory>
#include <unordered_map>

namespace Vida {

class Renderer3D {
public:
  explicit Renderer3D(Window &window);
  ~Renderer3D();

  Renderer3D(const Renderer3D &) = delete;
  Renderer3D &operator=(const Renderer3D &) = delete;

  void Clear(ColorRGBA color);
  void Present();

  void SetCamera(const Camera &camera);
  Camera &GetCamera() { return camera; }

  void DrawMesh(const Mesh &mesh, const Mat4 &transform, ColorRGBA color);
  void DrawQuad(Vec2 position, Vec2 size, ColorRGBA color);
  void DrawCube(Vec3 position, Vec3 size, ColorRGBA color);
  void DrawSphere(Vec3 position, float radius, ColorRGBA color);
  void DrawCone(Vec3 position, float radius, float height, ColorRGBA color);
  void DrawPyramid(Vec3 position, Vec3 size, ColorRGBA color);

  void SetShader(std::unique_ptr<Shader> shader);
  void ResetShader();

  Window &GetWindow() { return window; }

private:
  struct GPUMesh {
    GLuint VAO = 0;
    GLuint VBO = 0;
    size_t vertex_count = 0;
  };

  Window &window;
  Camera camera;

  std::unique_ptr<Shader> default_shader;
  GLuint VAO, VBO;

  void InitBuffers();

  std::unordered_map<const Vertex *, GPUMesh> mesh_cache;
  inline const GPUMesh &GetOrUpload(const Mesh &mesh) {
    const Vertex *key = mesh.vertices.data();

    auto it = mesh_cache.find(key);
    if (it != mesh_cache.end())
      return it->second;

    GPUMesh gpu;
    gpu.vertex_count = mesh.vertices.size();

    glGenVertexArrays(1, &gpu.VAO);
    glGenBuffers(1, &gpu.VBO);

    glBindVertexArray(gpu.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, gpu.VBO);
    glBufferData(GL_ARRAY_BUFFER, gpu.vertex_count * sizeof(Vertex),
                 mesh.vertices.data(), GL_STATIC_DRAW);

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

    mesh_cache[key] = gpu;
    return mesh_cache[key];
  }
};
} // namespace Vida
