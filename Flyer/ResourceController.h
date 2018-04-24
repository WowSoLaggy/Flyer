#pragma once

class IResource;
class RenderDevice;


class ResourceController
{
public:

  void indexResources();
  void clearIndices();

  void loadResources(RenderDevice& i_renderDevice);
  void unloadResources();

private:

  std::vector<std::shared_ptr<IResource>> d_resources;

  void indexResources(const std::string& i_dirName);

};
