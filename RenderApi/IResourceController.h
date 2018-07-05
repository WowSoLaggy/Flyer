#pragma once

#include "RenderApiFwd.h"


class IResourceController
{
public:

  static std::shared_ptr<IResourceController> create();

public:

  virtual ~IResourceController() = default;

  virtual ResourceId getMeshResourceId(const std::string& i_resourceName) const = 0;
  virtual ResourceId getTextureResourceId(const std::string& i_resourceName) const = 0;

  virtual void initialize() = 0;
  virtual void dispose() = 0;

  virtual void loadResources() = 0;
  virtual void unloadResources() = 0;

};
