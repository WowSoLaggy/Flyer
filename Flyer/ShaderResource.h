#pragma once

#include "IResource.h"


class ShaderResource : public IResource
{
public:

  ShaderResource(const std::string& i_fileName);

  virtual ResourceType getResourceType() const override { return ResourceType::Shader; }

  virtual void load(RenderDevice& i_renderDevice) override;
  virtual void unload() override;

private:

  std::string d_fileName;

};
