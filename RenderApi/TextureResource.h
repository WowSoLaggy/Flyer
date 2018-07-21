#pragma once

#include "IResource.h"


class TextureResource: public IResource
{
public:

  virtual ResourceType getResourceType() const override final { return ResourceType::Texture; }

  virtual void load(IRenderDevice& i_renderDevice) override;
  virtual void unload() override;
};
