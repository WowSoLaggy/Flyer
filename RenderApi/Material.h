#pragma once


struct Material
{
  std::string name;

  XMFLOAT4 ambientColor;
  XMFLOAT4 diffuseColor;
};

struct MaterialSpan
{
  Material material;

  int startIndex;
  int count;
};

using MaterialSequence = std::vector<MaterialSpan>;
