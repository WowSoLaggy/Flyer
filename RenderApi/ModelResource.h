#pragma once

#include "Resource.h"


class ModelResource : public Resource
{
public:

  virtual ResourceType getResourceType() const override final { return ResourceType::Model; }

  virtual void load() override;
  virtual void unload() override;
};
