#include "stdafx.h"
#include "MeshLoader.h"


void MeshLoader::loadMeshInfoFromFile(
  const std::string& i_filePath,
  std::vector<VertexTypePosTexNorm>& o_vertices,
  std::vector<int>& o_indices)
{
  o_vertices.clear();
  o_indices.clear();

  std::vector<XMFLOAT3> positions;
  std::vector<XMFLOAT2> texCoords;
  std::vector<XMFLOAT3> normals;

  std::map<std::tuple<int, int, int>, int> trioMap;
  int nextIndex = 0;

  std::ifstream file(i_filePath);
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
      for (int trioNum = 1; trioNum < 4; ++trioNum)
      {
        auto indicesTrio = Utils::splitString(tokens[trioNum], '/', true);
        int posIndex = std::atoi(indicesTrio[0].c_str()) - 1;
        int texCoordIndex = std::atoi(indicesTrio[1].c_str()) - 1;
        int normIndex = std::atoi(indicesTrio[2].c_str()) - 1;
        auto trio = std::tuple<int, int, int>(posIndex, texCoordIndex, normIndex);

        auto it = trioMap.find(trio);
        if (it == trioMap.end())
        {
          o_vertices.push_back({ positions[posIndex], texCoords[texCoordIndex], normals[normIndex] });
          trioMap[trio] = nextIndex;
          o_indices.push_back(nextIndex);
          ++nextIndex;
        }
        else
          o_indices.push_back(it->second);
      }
    }
  }
}
