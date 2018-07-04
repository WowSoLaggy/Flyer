#pragma once

#include "Resource.h"


class TextureResource: public Resource
{
public:

  virtual ResourceType getResourceType() const override final { return ResourceType::Texture; }

  virtual void load() override;
  virtual void unload() override;
};
