#include "stdafx.h"
#include "TextureLightShader.h"

#include "Buffers.h"
#include "DirectionalLight.h"
#include "Material.h"
#include "RenderDevice.h"
#include "Utils.h"


void TextureLightShader::load(RenderDevice& i_renderDevice)
{
  ID3D10Blob* vertexShaderBuffer = nullptr;
  D3DReadFileToBlob(L"Data\\TextureLightVS.vs", &vertexShaderBuffer);

  ID3D10Blob* pixelShaderBuffer = nullptr;
  D3DReadFileToBlob(L"Data\\TextureLightPS.ps", &pixelShaderBuffer);

  //

  i_renderDevice.getDevicePtr()->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
    vertexShaderBuffer->GetBufferSize(), NULL, &d_vertexShader);

  i_renderDevice.getDevicePtr()->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),
    pixelShaderBuffer->GetBufferSize(), NULL, &d_pixelShader);

  //

  D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
  
  polygonLayout[0].SemanticName = "POSITION";
  polygonLayout[0].SemanticIndex = 0;
  polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
  polygonLayout[0].InputSlot = 0;
  polygonLayout[0].AlignedByteOffset = 0;
  polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  polygonLayout[0].InstanceDataStepRate = 0;

  polygonLayout[1].SemanticName = "TEXCOORD";
  polygonLayout[1].SemanticIndex = 0;
  polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
  polygonLayout[1].InputSlot = 0;
  polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
  polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  polygonLayout[1].InstanceDataStepRate = 0;

  polygonLayout[2].SemanticName = "NORMAL";
  polygonLayout[2].SemanticIndex = 0;
  polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
  polygonLayout[2].InputSlot = 0;
  polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
  polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  polygonLayout[2].InstanceDataStepRate = 0;

  unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);
  
  //

  i_renderDevice.getDevicePtr()->CreateInputLayout(polygonLayout, numElements,
    vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &d_layout);

  vertexShaderBuffer->Release();
  pixelShaderBuffer->Release();

  //

  D3D11_SAMPLER_DESC samplerDesc;
  samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  samplerDesc.MipLODBias = 0.0f;
  samplerDesc.MaxAnisotropy = 1;
  samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
  samplerDesc.BorderColor[0] = 0;
  samplerDesc.BorderColor[1] = 0;
  samplerDesc.BorderColor[2] = 0;
  samplerDesc.BorderColor[3] = 0;
  samplerDesc.MinLOD = 0;
  samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

  D3D11_BUFFER_DESC matrixBufferDesc;
  matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  matrixBufferDesc.ByteWidth = sizeof(MatrixBuffer);
  matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  matrixBufferDesc.MiscFlags = 0;
  matrixBufferDesc.StructureByteStride = 0;

  D3D11_BUFFER_DESC lightBufferDesc;
  lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  lightBufferDesc.ByteWidth = sizeof(LightBuffer);
  lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  lightBufferDesc.MiscFlags = 0;
  lightBufferDesc.StructureByteStride = 0;

  //

  i_renderDevice.getDevicePtr()->CreateSamplerState(&samplerDesc, &d_sampleState);
  i_renderDevice.getDevicePtr()->CreateBuffer(&matrixBufferDesc, nullptr, &d_matrixBuffer);
  i_renderDevice.getDevicePtr()->CreateBuffer(&lightBufferDesc, nullptr, &d_lightBuffer);
}

void TextureLightShader::unload()
{
  d_lightBuffer->Release();
  d_matrixBuffer->Release();
  d_sampleState->Release();
  d_layout->Release();
  d_pixelShader->Release();
  d_vertexShader->Release();
}


void TextureLightShader::setParameters(RenderDevice& i_renderDevice,
  XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
  ID3D11ShaderResourceView* texture, const DirectionalLight& i_directionalLight,
  const Material& i_material)
{
  worldMatrix = XMMatrixTranspose(worldMatrix);
  viewMatrix = XMMatrixTranspose(viewMatrix);
  projectionMatrix = XMMatrixTranspose(projectionMatrix);

  //

  D3D11_MAPPED_SUBRESOURCE mappedResource;
  i_renderDevice.getDeviceContextPtr()->Map(d_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

  auto* dataPtr = (MatrixBuffer*)mappedResource.pData;
  dataPtr->world = worldMatrix;
  dataPtr->view = viewMatrix;
  dataPtr->projection = projectionMatrix;

  i_renderDevice.getDeviceContextPtr()->Unmap(d_matrixBuffer, 0);

  //

  i_renderDevice.getDeviceContextPtr()->VSSetConstantBuffers(0, 1, &d_matrixBuffer);
  i_renderDevice.getDeviceContextPtr()->PSSetShaderResources(0, 1, &texture);

  //

  i_renderDevice.getDeviceContextPtr()->Map(d_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

  auto* dataPtr2 = (LightBuffer*)mappedResource.pData;
  dataPtr2->diffuseColor = i_material.diffuseColor;
  dataPtr2->lightColor = i_directionalLight.getColor();
  dataPtr2->lightDirection = i_directionalLight.getDirection();
  dataPtr2->ambientStrength = i_directionalLight.getAmbientPower();

  i_renderDevice.getDeviceContextPtr()->Unmap(d_lightBuffer, 0);

  //

  i_renderDevice.getDeviceContextPtr()->PSSetConstantBuffers(0, 1, &d_lightBuffer);
}


void TextureLightShader::render(RenderDevice& i_renderDevice, int i_offset, int i_indicesCount)
{
  i_renderDevice.getDeviceContextPtr()->IASetInputLayout(d_layout);

  i_renderDevice.getDeviceContextPtr()->VSSetShader(d_vertexShader, NULL, 0);
  i_renderDevice.getDeviceContextPtr()->PSSetShader(d_pixelShader, NULL, 0);

  i_renderDevice.getDeviceContextPtr()->PSSetSamplers(0, 1, &d_sampleState);

  i_renderDevice.getDeviceContextPtr()->DrawIndexed(i_indicesCount, i_offset, 0);
}
