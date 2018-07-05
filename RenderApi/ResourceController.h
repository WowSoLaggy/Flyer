#pragma once

#include "IResourceController.h"
#include "MeshResource.h"
#include "TextureResource.h"


class ResourceController: public IResourceController
{
public:

  virtual ResourceId getMeshResourceId(const std::string& i_resourceName) const override;
  virtual ResourceId getTextureResourceId(const std::string& i_resourceName) const override;

  const MeshResource& getMeshResource(ResourceId i_resourceId) const;
  const TextureResource& getTextureResource(ResourceId i_resourceId) const;

  virtual void initialize() override;
  virtual void dispose() override;

  virtual void loadResources() override;
  virtual void unloadResources() override;

private:

  std::unordered_map<std::string, ResourceId> d_resourceIdsMap;
  std::unordered_map<ResourceId, std::shared_ptr<IResource>> d_resourceMap;

};
