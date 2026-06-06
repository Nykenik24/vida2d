#pragma once

#include "vida/core/Math.hpp"
#include <glad/glad.h>
#include <string>

namespace Vida {

class Shader {
public:
  Shader(const std::string &vert_path, const std::string &frag_path);
  ~Shader();

  Shader(const Shader &) = delete;
  Shader &operator=(const Shader &) = delete;

  void Bind() const;
  void Unbind() const;

  void SetInt(const std::string &name, int value) const;
  void SetFloat(const std::string &name, float value) const;
  void SetVec2(const std::string &name, const Vec2 &value) const;
  void SetVec3(const std::string &name, const Vec3 &value) const;
  void SetVec4(const std::string &name, const Vec4 &value) const;
  void SetMat4(const std::string &name, const Mat4 &value) const;

  GLuint Handle() const { return program; }

private:
  GLuint program;

  static std::string ReadFile(const std::string &path);
  static GLuint Compile(GLenum type, const std::string &src);
  GLint Location(const std::string &name) const;
};

} // namespace Vida
