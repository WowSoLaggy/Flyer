#pragma once

#include "IResourceController.h"


class ResourceController: public IResourceController
{
public:

  virtual ResourceDesc getResourceDesc() const override;

  virtual void initialize() override;
  virtual void dispose() override;

  virtual void loadResources() override;
  virtual void unloadResources() override;

};
