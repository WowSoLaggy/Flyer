#pragma once

#include "IResource.h"


class ModelResource : public IResource
{
public:

  virtual ResourceType getResourceType() const override { return ResourceType::Model; }

  virtual void load() override;
  virtual void unload() override;
};
