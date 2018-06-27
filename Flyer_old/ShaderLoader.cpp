#include "stdafx.h"
#include "ShaderLoader.h"

#include "RenderDevice.h"
#include "Utils.h"


void ShaderLoader::loadVertexShader(const std::string& i_fileName,
  RenderDevice& i_renderDevice, ID3D11VertexShader*& i_vertexShader)
{
  ID3D10Blob* vertexShaderBuffer = nullptr;
  D3DReadFileToBlob(Utils::getWString(i_fileName).c_str(), &vertexShaderBuffer);

  i_renderDevice.getDevicePtr()->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
    vertexShaderBuffer->GetBufferSize(), NULL, &i_vertexShader);

  vertexShaderBuffer->Release();
}

void ShaderLoader::loadPixelShader(const std::string& i_fileName,
  RenderDevice& i_renderDevice, ID3D11PixelShader*& i_pixelShader)
{
  ID3D10Blob* pixelShaderBuffer = nullptr;
  D3DReadFileToBlob(Utils::getWString(i_fileName).c_str(), &pixelShaderBuffer);

  i_renderDevice.getDevicePtr()->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),
    pixelShaderBuffer->GetBufferSize(), NULL, &i_pixelShader);

  pixelShaderBuffer->Release();
}
