#pragma once

#include "RenderApiFwd.h"

#include <Sdk/Vector.h>


class IObject3d
{
public:

  virtual ~IObject3d() = default;

  virtual ResourceId getMeshResourceId() const = 0;
  virtual ResourceId getTextureResourceId() const = 0;

  virtual Vector3 getPosition() const = 0;

};
