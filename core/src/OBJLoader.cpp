#include "vida/core/OBJLoader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace Vida {

Mesh OBJLoader::Load(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open())
    throw std::runtime_error("Failed to open OBJ file: " + path);

  std::vector<Vec3> positions;
  std::vector<Vec2> uvs;
  std::vector<Vec3> normals;

  Mesh mesh;

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#')
      continue;

    std::istringstream ss(line);
    std::string token;
    ss >> token;

    if (token == "v") {
      Vec3 p;
      ss >> p.x >> p.y >> p.z;
      positions.push_back(p);

    } else if (token == "vt") {
      Vec2 uv;
      ss >> uv.x >> uv.y;
      uvs.push_back(uv);

    } else if (token == "vn") {
      Vec3 n;
      ss >> n.x >> n.y >> n.z;
      normals.push_back(n);

    } else if (token == "f") {
      std::string face_token;
      std::vector<Vertex> face_verts;

      while (ss >> face_token) {
        std::istringstream ft(face_token);
        std::string pi, uvi, ni;

        std::getline(ft, pi, '/');
        std::getline(ft, uvi, '/');
        std::getline(ft, ni);

        Vertex v = {};

        if (!pi.empty())
          v.position = positions[std::stoi(pi) - 1];

        if (!uvi.empty())
          v.uv = uvs[std::stoi(uvi) - 1];

        if (!ni.empty())
          v.normal = normals[std::stoi(ni) - 1];

        face_verts.push_back(v);
      }

      for (size_t i = 1; i + 1 < face_verts.size(); i++) {
        mesh.vertices.push_back(face_verts[0]);
        mesh.vertices.push_back(face_verts[i]);
        mesh.vertices.push_back(face_verts[i + 1]);
      }
    }
  }

  if (mesh.vertices.empty())
    throw std::runtime_error("OBJ file has no geometry: " + path);

  return mesh;
}

} // namespace Vida
