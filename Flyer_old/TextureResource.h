#pragma once

#include "IResource.h"


class TextureResource : public IResource
{
public:

  TextureResource(const std::string& i_textureName);

  virtual ResourceType getResourceType() const override { return ResourceType::Texture; }
  virtual const std::string& getResourceName() const override { return d_textureName; }

  virtual void load(RenderDevice& i_renderDevice) override;
  virtual void unload() override;

private:

  const std::string d_textureName;

};
