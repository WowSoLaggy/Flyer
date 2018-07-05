#pragma once

#include "RenderApiFwd.h"

#include <Sdk/Vector.h>


class IObject3D
{
public:

  virtual ~IObject3D() = default;

  virtual ResourceId getMeshResourceId() const = 0;
  virtual ResourceId getTextureResourceId() const = 0;

  virtual Vector3 getPosition() const = 0;

};
