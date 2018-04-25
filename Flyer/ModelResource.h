#pragma once

#include "IResource.h"


class ModelResource : public IResource
{
public:

  ModelResource(const std::string& i_modelName);

  virtual ResourceType getResourceType() const override { return ResourceType::Model; }

  virtual void load(RenderDevice& i_renderDevice) override;
  virtual void unload() override;

private:

  const std::string d_modelName;

};
