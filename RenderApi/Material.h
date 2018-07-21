#pragma once


struct Material
{
  std::string name;

  XMFLOAT4 ambientColor;
  XMFLOAT4 diffuseColor;

  static Material getDefault() { return { "", { 1, 1, 1, 1}, {1, 1, 1, 1} }; }
};
