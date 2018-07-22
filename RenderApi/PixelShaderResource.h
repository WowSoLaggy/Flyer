#pragma once

#include "IResource.h"


class PixelShaderResource : public IResource
{
public:

  PixelShaderResource(const std::string& i_shaderFilePath);

  virtual void load(IRenderDevice& i_renderDevice) override;
  virtual void unload() override;

private:

  const std::string d_shaderFilePath;

  ID3D11PixelShader* d_pixelShader;
};
