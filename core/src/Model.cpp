#include "vida/core/Model.hpp"
#include "vida/core/ModelLoader.hpp"

namespace Vida {
Model::Model(const std::string &path) : mesh(ModelLoader::Load(path)) {}
Model::Model(const Mesh &mesh) : mesh(mesh) {}
} // namespace Vida
