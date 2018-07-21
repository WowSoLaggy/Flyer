#pragma once

#include "IResourceController.h"
#include "MeshResource.h"
#include "RenderApiFwd.h"
#include "TextureResource.h"


class ResourceController: public IResourceController
{
public:

  virtual ResourceId getResourceId(const std::string& i_resourceName) const override;

  const MeshResource& getMeshResource(ResourceId i_resourceId) const;
  const TextureResource& getTextureResource(ResourceId i_resourceId) const;

  virtual void initialize(const std::string& i_resourcesFolder) override;
  virtual void dispose() override;

  virtual void loadResources(IRenderDevice& i_renderDevice) override;
  virtual void unloadResources() override;

private:

  std::unordered_map<std::string, ResourceId> d_nameToIdMap;
  std::unordered_map<ResourceId, std::shared_ptr<IResource>> d_idToResourceMap;

  ResourceId d_nextResourceId;
  ResourceId getFreeResourceId();

  void indexResourcesInDir(const std::string& i_dirName);
  void clearResoures();

};
