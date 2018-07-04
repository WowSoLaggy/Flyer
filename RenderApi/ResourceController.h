#pragma once

#include "IResourceController.h"


class ResourceController: public IResourceController
{
public:

  virtual ResourceId getResourceIdModel() const override;
  virtual ResourceId getResourceIdTexture() const override;

  virtual void initialize() override;
  virtual void dispose() override;

  virtual void loadResources() override;
  virtual void unloadResources() override;

};
