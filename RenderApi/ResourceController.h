#pragma once

#include "IResourceController.h"
#include "ModelResource.h"
#include "TextureResource.h"


class ResourceController: public IResourceController
{
public:

  virtual ResourceId getModelResourceId() const override;
  virtual ResourceId getTextureResourceId() const override;

  const ModelResource& getModelResource(ResourceId i_resourceId) const;
  const TextureResource& getTextureResource(ResourceId i_resourceId) const;

  virtual void initialize() override;
  virtual void dispose() override;

  virtual void loadResources() override;
  virtual void unloadResources() override;

private:

  std::unordered_map<ResourceId, std::shared_ptr<IResource>> d_resources;

};
