#pragma once

#include "RenderApiFwd.h"

#include <Sdk/Vector.h>


struct Material
{
  std::string name;

  Vector4 ambientColor;
  Vector4 diffuseColor;

  static Material getDefault() { return { "", { 1, 1, 1, 1}, {1, 1, 1, 1} }; }
};
