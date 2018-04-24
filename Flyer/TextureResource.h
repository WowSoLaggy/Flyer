#pragma once

#include "IResource.h"


class TextureResource : public IResource
{
public:

  TextureResource(const std::string& i_textureName);

  virtual ResourceType getResourceType() const override { return ResourceType::Texture; }

  virtual void load(RenderDevice& i_renderDevice) override;
  virtual void unload() override;

private:

  std::string d_textureName;

};
