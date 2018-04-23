#pragma once

#include "IResource.h"


class ModelResource : public IResource
{
public:

  ModelResource(const std::string& i_modelName);

  virtual ResourceType getResourceType() const override { return ResourceType::Model; }

  virtual void load() override;
  virtual void unload() override;

private:

  std::string d_modelName;

};
