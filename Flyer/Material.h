#pragma once


struct Material
{
  std::string name;

  XMFLOAT4 ambientColor;
  XMFLOAT4 diffuseColor;
};


struct MaterialSequence
{
  std::vector<std::pair<int, Material>> frameToMaterialPairs;
};
