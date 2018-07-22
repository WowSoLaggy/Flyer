#pragma once

#include "IResource.h"


class TextureResource: public IResource
{
public:

  TextureResource(const std::string& i_textureFilePath);

  virtual void load(IRenderDevice& i_renderDevice) override;
  virtual void unload() override;

private:

  const std::string d_textureFilePath;

  ID3D11ShaderResourceView* d_texture;

};
