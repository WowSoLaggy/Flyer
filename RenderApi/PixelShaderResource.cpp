#include "stdafx.h"
#include "PixelShaderResource.h"

#include "RenderDevice.h"

#include <Sdk/StringUtils.h>


PixelShaderResource::PixelShaderResource(const std::string& i_shaderFilePath)
  : d_shaderFilePath(i_shaderFilePath)
{
}


void PixelShaderResource::load(IRenderDevice& i_renderDevice)
{
  auto& renderDevice = dynamic_cast<RenderDevice&>(i_renderDevice);

  ID3D10Blob* pixelShaderBuffer = nullptr;
  D3DReadFileToBlob(Utils::getWString(d_shaderFilePath).c_str(), &pixelShaderBuffer);

  renderDevice.getDevicePtr()->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),
    pixelShaderBuffer->GetBufferSize(), NULL, &d_pixelShader);

  pixelShaderBuffer->Release();
}

void PixelShaderResource::unload()
{
  d_pixelShader->Release();
}
