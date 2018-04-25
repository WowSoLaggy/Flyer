#pragma once

#include "IResource.h"


enum class ShaderType
{
  Vertex,
  Pixel,
};


class ShaderResource : public IResource
{
public:

  ShaderResource(const std::string& i_fileName, ShaderType i_shaderType);

  virtual ResourceType getResourceType() const override { return ResourceType::Shader; }

  virtual void load(RenderDevice& i_renderDevice) override;
  virtual void unload() override;

private:

  const std::string d_fileName;
  const ShaderType d_shaderType;

};
