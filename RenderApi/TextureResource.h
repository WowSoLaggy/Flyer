#pragma once

#include "IResource.h"


class TextureResource: public IResource
{
public:


  virtual void load(IRenderDevice& i_renderDevice) override;
  virtual void unload() override;
};
