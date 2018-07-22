#pragma once

#include "IResource.h"


class VertexShaderResource: public IResource
{
public:

  VertexShaderResource(const std::string& i_shaderFilePath);

  virtual void load(IRenderDevice& i_renderDevice) override;
  virtual void unload() override;

private:

  const std::string d_shaderFilePath;

  ID3D11VertexShader* d_vertexShader;
  ID3D11InputLayout* d_layout;
};
