#include "stdafx.h"
#include "SimpleTextureShader.h"


SimpleTextureShader::SimpleTextureShader()
{
  d_vertexShader = 0;
  d_pixelShader = 0;
  d_layout = 0;
  d_matrixBuffer = 0;
  d_sampleState = 0;
}


bool SimpleTextureShader::Initialize(ID3D11Device* device, HWND hwnd)
{
  bool result;

  // Initialize the vertex and pixel shaders.
  result = InitializeShader(device, hwnd);
  if (!result)
    return false;

  return true;
}

void SimpleTextureShader::Shutdown()
{
  // Shutdown the vertex and pixel shaders as well as the related objects.
  ShutdownShader();

  return;
}


bool SimpleTextureShader::Render(ID3D11DeviceContext* deviceContext, int indexCount,
  XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
  bool result;

  // Set the shader parameters that it will use for rendering.
  result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture);
  if (!result)
    return false;

  // Now render the prepared buffers with the shader.
  RenderShader(deviceContext, indexCount);

  return true;
}

bool SimpleTextureShader::InitializeShader(ID3D11Device* device, HWND hwnd)
{
  HRESULT result;
  ID3D10Blob* errorMessage;
  ID3D10Blob* vertexShaderBuffer;
  ID3D10Blob* pixelShaderBuffer;
  D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
  unsigned int numElements;
  D3D11_BUFFER_DESC matrixBufferDesc;
  D3D11_SAMPLER_DESC samplerDesc;

  // Initialize the pointers this function will use to null.
  errorMessage = 0;
  vertexShaderBuffer = 0;
  pixelShaderBuffer = 0;

  // Compile the vertex shader code.
  result = D3DCompileFromFile(L"SimpleTextureVS.hlsl", NULL, NULL,
    "main", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, NULL,
    &vertexShaderBuffer, &errorMessage);
  if (FAILED(result))
    return false;

  // Compile the pixel shader code.
  result = D3DCompileFromFile(L"SimpleTexturePS.hlsl", NULL, NULL,
    "main", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, NULL,
    &pixelShaderBuffer, &errorMessage);
  if (FAILED(result))
    return false;

  // Create the vertex shader from the buffer.
  result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
    vertexShaderBuffer->GetBufferSize(), NULL, &d_vertexShader);
  if (FAILED(result))
    return false;

  // Create the pixel shader from the buffer.
  result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),
    pixelShaderBuffer->GetBufferSize(), NULL, &d_pixelShader);
  if (FAILED(result))
    return false;

  // Create the vertex input layout description.
  // This setup needs to match the VertexType stucture in the ModelClass and in the shader.
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

  // Get a count of the elements in the layout.
  numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

  // Create the vertex input layout.
  result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
    vertexShaderBuffer->GetBufferSize(), &d_layout);
  if (FAILED(result))
    return false;

  // Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
  vertexShaderBuffer->Release();
  vertexShaderBuffer = 0;

  pixelShaderBuffer->Release();
  pixelShaderBuffer = 0;

  // Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
  matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
  matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  matrixBufferDesc.MiscFlags = 0;
  matrixBufferDesc.StructureByteStride = 0;

  // Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
  result = device->CreateBuffer(&matrixBufferDesc, NULL, &d_matrixBuffer);
  if (FAILED(result))
    return false;

  // Create a texture sampler state description.
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

  // Create the texture sampler state.
  result = device->CreateSamplerState(&samplerDesc, &d_sampleState);
  if (FAILED(result))
    return false;

  return true;
}

void SimpleTextureShader::ShutdownShader()
{
  // Release the sampler state.
  if (d_sampleState)
  {
    d_sampleState->Release();
    d_sampleState = 0;
  }

  // Release the matrix constant buffer.
  if (d_matrixBuffer)
  {
    d_matrixBuffer->Release();
    d_matrixBuffer = 0;
  }

  // Release the layout.
  if (d_layout)
  {
    d_layout->Release();
    d_layout = 0;
  }

  // Release the pixel shader.
  if (d_pixelShader)
  {
    d_pixelShader->Release();
    d_pixelShader = 0;
  }

  // Release the vertex shader.
  if (d_vertexShader)
  {
    d_vertexShader->Release();
    d_vertexShader = 0;
  }
}

bool SimpleTextureShader::SetShaderParameters(ID3D11DeviceContext* deviceContext,
  XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
  HRESULT result;
  D3D11_MAPPED_SUBRESOURCE mappedResource;
  MatrixBufferType* dataPtr;
  unsigned int bufferNumber;

  // Transpose the matrices to prepare them for the shader.
  worldMatrix = XMMatrixTranspose(worldMatrix);
  viewMatrix = XMMatrixTranspose(viewMatrix);
  projectionMatrix = XMMatrixTranspose(projectionMatrix);

  // Lock the constant buffer so it can be written to.
  result = deviceContext->Map(d_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    return false;

  // Get a pointer to the data in the constant buffer.
  dataPtr = (MatrixBufferType*)mappedResource.pData;

  // Copy the matrices into the constant buffer.
  dataPtr->world = worldMatrix;
  dataPtr->view = viewMatrix;
  dataPtr->projection = projectionMatrix;

  // Unlock the constant buffer.
  deviceContext->Unmap(d_matrixBuffer, 0);

  // Set the position of the constant buffer in the vertex shader.
  bufferNumber = 0;

  // Now set the constant buffer in the vertex shader with the updated values.
  deviceContext->VSSetConstantBuffers(bufferNumber, 1, &d_matrixBuffer);

  // Set shader texture resource in the pixel shader.
  deviceContext->PSSetShaderResources(0, 1, &texture);

  return true;
}

void SimpleTextureShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
  // Set the vertex input layout.
  deviceContext->IASetInputLayout(d_layout);

  // Set the vertex and pixel shaders that will be used to render this triangle.
  deviceContext->VSSetShader(d_vertexShader, NULL, 0);
  deviceContext->PSSetShader(d_pixelShader, NULL, 0);

  // Set the sampler state in the pixel shader.
  deviceContext->PSSetSamplers(0, 1, &d_sampleState);

  // Render the triangle.
  deviceContext->DrawIndexed(indexCount, 0, 0);
}
