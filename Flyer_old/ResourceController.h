#pragma once

class IResource;
class RenderDevice;

using ResourceId = int;
#define INVALID_RESOURCE_ID (ResourceId)-1;


class ResourceController
{
public:

  void indexResources();
  void clearIndices();

  void loadResources(RenderDevice& i_renderDevice);
  void unloadResources();

  ResourceId getResourceId(const std::string& i_resourceName) const;
  std::shared_ptr<IResource> getResource(ResourceId i_resourceId);

private:

  std::map<ResourceId, std::shared_ptr<IResource>> d_resources;

  ResourceId d_nextResourceId;
  ResourceId getFreeResourceId();

  void indexResources(const std::string& i_dirName);

};
