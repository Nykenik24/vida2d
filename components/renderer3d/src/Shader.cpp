#include "vida/renderer3d/Shader.hpp"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <stdexcept>

namespace Vida {

Shader::Shader(const std::string &vert_path, const std::string &frag_path) {
  std::string vert_src = ReadFile(vert_path);
  std::string frag_src = ReadFile(frag_path);

  GLuint vert = Compile(GL_VERTEX_SHADER, vert_src);
  GLuint frag = Compile(GL_FRAGMENT_SHADER, frag_src);

  program = glCreateProgram();
  glAttachShader(program, vert);
  glAttachShader(program, frag);
  glLinkProgram(program);

  int ok;
  glGetProgramiv(program, GL_LINK_STATUS, &ok);
  if (!ok) {
    char log[512];
    glGetProgramInfoLog(program, 512, nullptr, log);
    throw std::runtime_error(std::string("Shader link error: ") + log);
  }

  glDeleteShader(vert);
  glDeleteShader(frag);
}

Shader::~Shader() { glDeleteProgram(program); }

void Shader::Bind() const { glUseProgram(program); }
void Shader::Unbind() const { glUseProgram(0); }

void Shader::SetInt(const std::string &name, int value) const {
  glUniform1i(Location(name), value);
}

void Shader::SetFloat(const std::string &name, float value) const {
  glUniform1f(Location(name), value);
}

void Shader::SetVec2(const std::string &name, const Vec2 &value) const {
  glUniform2fv(Location(name), 1, glm::value_ptr(value));
}

void Shader::SetVec3(const std::string &name, const Vec3 &value) const {
  glUniform3fv(Location(name), 1, glm::value_ptr(value));
}

void Shader::SetVec4(const std::string &name, const Vec4 &value) const {
  glUniform4fv(Location(name), 1, glm::value_ptr(value));
}

void Shader::SetMat4(const std::string &name, const Mat4 &value) const {
  glUniformMatrix4fv(Location(name), 1, GL_FALSE, glm::value_ptr(value));
}

GLint Shader::Location(const std::string &name) const {
  GLint loc = glGetUniformLocation(program, name.c_str());
  return loc;
}

std::string Shader::ReadFile(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open())
    throw std::runtime_error("Failed to open shader file: " + path);

  std::stringstream ss;
  ss << file.rdbuf();
  return ss.str();
}

GLuint Shader::Compile(GLenum type, const std::string &src) {
  const char *c_src = src.c_str();
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &c_src, nullptr);
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

} // namespace Vida
