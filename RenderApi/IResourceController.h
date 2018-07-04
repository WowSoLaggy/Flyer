#pragma once

#include "RenderApiFwd.h"


struct ResourceDesc
{
  const ResourceId resourceId;
  const IResourceController& resourceControllerPtr;
};


class IResourceController
{
public:

  static std::shared_ptr<IResourceController> create();

public:

  virtual ~IResourceController() = default;

  virtual ResourceDesc getResourceDesc() const = 0;

  virtual void initialize() = 0;
  virtual void dispose() = 0;

  virtual void loadResources() = 0;
  virtual void unloadResources() = 0;

};
