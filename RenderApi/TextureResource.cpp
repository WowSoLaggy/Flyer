#include "stdafx.h"
#include "TextureResource.h"

#include "RenderDevice.h"

#include <Sdk/StringUtils.h>


TextureResource::TextureResource(std::string i_textureFilePath)
  : d_textureFilePath(std::move(i_textureFilePath))
{
}


void TextureResource::load(IRenderDevice& i_renderDevice)
{
  auto& renderDevice = dynamic_cast<RenderDevice&>(i_renderDevice);

  CreateDDSTextureFromFile(renderDevice.getDevicePtr(),
    Utils::getWString(d_textureFilePath).c_str(), nullptr, &d_texture);
}

void TextureResource::unload()
{
  d_texture->Release();
}
