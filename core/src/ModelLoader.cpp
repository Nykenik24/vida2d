#include "vida/core/ModelLoader.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <stdexcept>

namespace Vida {
static void GenerateSphericalUVs(Mesh &mesh) {
  for (auto &vertex : mesh.vertices) {
    Vec3 n = glm::normalize(vertex.position);
    float u = 0.5f + atan2f(n.z, n.x) / (2.0f * M_PI);
    float v = 0.5f - asinf(n.y) / M_PI;
    vertex.uv = Vec2(u, v);
  }
}

Mesh ModelLoader::Load(const std::string &path) {
  Assimp::Importer importer;

  const aiScene *scene = importer.ReadFile(
      path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                aiProcess_CalcTangentSpace | aiProcess_FlipUVs |
                aiProcess_JoinIdenticalVertices);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    throw std::runtime_error("Failed to load model: " +
                             std::string(importer.GetErrorString()));

  Mesh mesh;

  bool has_uvs = false;

  for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
    aiMesh *ai_mesh = scene->mMeshes[m];

    std::vector<Vertex> temp;
    temp.reserve(ai_mesh->mNumVertices);

    for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++) {
      Vertex v = {};

      v.position = Vec3(ai_mesh->mVertices[i].x, ai_mesh->mVertices[i].y,
                        ai_mesh->mVertices[i].z);

      if (ai_mesh->HasNormals())
        v.normal = Vec3(ai_mesh->mNormals[i].x, ai_mesh->mNormals[i].y,
                        ai_mesh->mNormals[i].z);

      if (ai_mesh->mTextureCoords[0]) {
        has_uvs = true;
        v.uv = Vec2(ai_mesh->mTextureCoords[0][i].x,
                    ai_mesh->mTextureCoords[0][i].y);
      }

      temp.push_back(v);
    }

    for (unsigned int i = 0; i < ai_mesh->mNumFaces; i++) {
      aiFace &face = ai_mesh->mFaces[i];
      for (unsigned int j = 0; j < face.mNumIndices; j++)
        mesh.vertices.push_back(temp[face.mIndices[j]]);
    }
  }

  if (mesh.vertices.empty())
    throw std::runtime_error("Model has no geometry: " + path);

  if (!has_uvs)
    GenerateSphericalUVs(mesh);

  return mesh;
}
} // namespace Vida
