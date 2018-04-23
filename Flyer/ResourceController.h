#pragma once

class IResource;


class ResourceController
{
public:

  void indexResources();

private:

  std::vector<std::shared_ptr<IResource>> d_resources;

  void indexResources(const std::string& i_dirName);

};
