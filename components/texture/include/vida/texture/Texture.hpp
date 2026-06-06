#pragma once

#include <glad/glad.h>
#include <string>

namespace Vida {
class Texture {
public:
  Texture(const std::string &path);
  ~Texture();

  Texture(const Texture &) = delete;
  Texture &operator=(const Texture &) = delete;

  void Bind(int slot = 0) const;
  void Unbind() const;

  int Width() const { return width; }
  int Height() const { return height; }
  GLuint Handle() const { return handle; }

private:
  GLuint handle;
  int width, height;
};
} // namespace Vida
