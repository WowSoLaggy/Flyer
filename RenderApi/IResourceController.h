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

  virtual ResourceDesc getResourceDesc() const = 0;

  virtual void initialize() = 0;
  virtual void dispose() = 0;

  virtual void loadResources() = 0;
  virtual void unloadResources() = 0;

private:

  IResourceController() = default;

};
