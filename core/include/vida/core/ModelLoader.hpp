#pragma once

#include "vida/core/Mesh.hpp"
#include <string>

namespace Vida {

class ModelLoader {
public:
  static Mesh Load(const std::string &path);
};

} // namespace Vida
