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

  static MaterialSequence createBlank()
  {
    MaterialSequence matSequence;
    matSequence.frameToMaterialPairs.push_back({ 0,
      { "blank",{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } } });

    return matSequence;
  }
};
