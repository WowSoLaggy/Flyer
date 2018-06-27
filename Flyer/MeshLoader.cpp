#include "stdafx.h"
#include "MeshLoader.h"


void MeshLoader::loadMeshInfoFromFile(
  const std::string& i_modelPath,
  const std::string& i_materialsPath,
  std::vector<VertexTypePosTexNorm>& o_vertices,
  std::vector<int>& o_indices,
  MaterialSequence& o_matSequence)
{
  o_vertices.clear();
  o_indices.clear();

  std::ifstream file(i_modelPath);
  if (!file)
    return;

  o_matSequence.frameToMaterialPairs.clear();
  auto materials = loadMaterials(i_materialsPath);

  std::vector<XMFLOAT3> positions;
  std::vector<XMFLOAT2> texCoords;
  std::vector<XMFLOAT3> normals;

  std::map<std::tuple<int, int, int>, int> trioMap;
  int nextIndex = 0;

  std::string line;
  while (std::getline(file, line))
  {
    auto tokens = Utils::splitString(line, '#', true);
    if (tokens.empty())
      continue;
    line = tokens.front();
    if (line.empty())
      continue;

    tokens = Utils::splitString(line, ' ', true);
    if (tokens[0] == "v")
    {
      positions.push_back({
      (float)std::atof(tokens[1].c_str()),
      (float)std::atof(tokens[2].c_str()),
      (float)std::atof(tokens[3].c_str()) });
    }
    else if (tokens[0] == "vt")
    {
      texCoords.push_back({
        (float)std::atof(tokens[1].c_str()),
        (float)std::atof(tokens[2].c_str()) });
    }
    else if (tokens[0] == "vn")
    {
      normals.push_back({
        (float)std::atof(tokens[1].c_str()),
        (float)std::atof(tokens[2].c_str()),
        (float)std::atof(tokens[3].c_str()) });
    }
    else if (tokens[0] == "f")
    {
      for (int trioNum : { 1, 2, 3 })
      {
        auto indicesTrio = Utils::splitString(tokens[trioNum], '/', true);
        int posIndex = std::atoi(indicesTrio[0].c_str()) - 1;
        int texCoordIndex = !indicesTrio[1].empty() ? std::atoi(indicesTrio[1].c_str()) - 1 : -1;
        int normIndex = std::atoi(indicesTrio[2].c_str()) - 1;
        auto trio = std::tuple<int, int, int>(posIndex, texCoordIndex, normIndex);

        auto it = trioMap.find(trio);
        if (it == trioMap.end())
        {
          XMFLOAT2 uv = (texCoordIndex == -1) ? XMFLOAT2( 0.0f, 0.0f ) : texCoords[texCoordIndex];
          o_vertices.push_back({ positions[posIndex], uv, normals[normIndex] });
          trioMap[trio] = nextIndex;
          o_indices.push_back(nextIndex);
          ++nextIndex;
        }
        else
          o_indices.push_back(it->second);
      }
    }
    else if (tokens[0] == "usemtl")
    {
      auto it = std::find_if(materials.begin(), materials.end(),
        [&](const Material& i_material) { return i_material.name == tokens[1]; });
      if (it == materials.end())
        continue;

      o_matSequence.frameToMaterialPairs.push_back({ (int)o_indices.size(), *it });
    }
  }

  if (o_matSequence.frameToMaterialPairs.empty())
  {
    // Insert blank material
    o_matSequence.frameToMaterialPairs.push_back({ 0,
      { "blank",{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } } });
  }
}

std::vector<Material> MeshLoader::loadMaterials(const std::string& i_materialsPath)
{
  std::vector<Material> materials;
  if (i_materialsPath.empty())
    return materials;

  std::ifstream file(i_materialsPath);
  if (!file)
    return materials;

  std::string line;
  Material material;
  while (std::getline(file, line))
  {
    auto tokens = Utils::splitString(line, '#', true);
    if (tokens.empty())
      continue;
    line = tokens.front();
    if (line.empty())
      continue;

    tokens = Utils::splitString(line, ' ', true);
    if (tokens[0] == "newmtl")
    {
      if (material.name != tokens[1])
      {
        if (!material.name.empty())
          materials.push_back(material);
        material = Material();
        material.name = tokens[1];
      }
    }
    else if (tokens[0] == "Ka")
    {
      material.ambientColor = {
        (float)std::atof(tokens[1].c_str()),
        (float)std::atof(tokens[2].c_str()),
        (float)std::atof(tokens[3].c_str()),
        1.0f };
    }
    else if (tokens[0] == "Kd")
    {
      material.diffuseColor = {
        (float)std::atof(tokens[1].c_str()),
        (float)std::atof(tokens[2].c_str()),
        (float)std::atof(tokens[3].c_str()),
        1.0f };
    }
  }

  if (!material.name.empty())
    materials.push_back(material);

  return materials;
}
