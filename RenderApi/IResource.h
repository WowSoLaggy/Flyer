#pragma once

#include "RenderApiFwd.h"


enum class ResourceType
{
  Texture,
  Mesh,
  Shader,
};


class IResource
{
public:

  virtual ~IResource() = default;

  virtual ResourceType getResourceType() const = 0;
  virtual ResourceId getResourceId() const = 0;

  virtual void load() = 0;
  virtual void unload() = 0;

};
