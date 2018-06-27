#include "stdafx.h"
#include "ModelClass.h"


ModelClass::ModelClass()
{
  d_vertexBuffer = 0;
  d_indexBuffer = 0;
  d_Texture = 0;
}


bool ModelClass::Initialize(ID3D11Device* device, const std::wstring& i_filename)
{
  bool result;

  // Initialize the vertex and index buffer that hold the geometry for the triangle.
  result = InitializeBuffers(device);
  if (!result)
    return false;

  // Load the texture for this model.
  result = LoadTexture(device, i_filename);
  if (!result)
    return false;

  return true;
}

void ModelClass::Shutdown()
{
  // Release the model texture.
  ReleaseTexture();

  // Release the vertex and index buffers.
  ShutdownBuffers();
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
  // Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
  RenderBuffers(deviceContext);
}

int ModelClass::GetIndexCount()
{
  return d_indexCount;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
  return d_Texture->GetTexture();
}


bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
  // Set the number of vertices in the vertex array.
  d_vertexCount = 3;

  // Set the number of indices in the index array.
  d_indexCount = 3;

  // Create the vertex array.
  VertexType* vertices = new VertexType[d_vertexCount];
  if (!vertices)
    return false;

  // Create the index array.
  unsigned long* indices = new unsigned long[d_indexCount];
  if (!indices)
    return false;

  // Load the vertex array with data.
  vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
  vertices[0].texture = XMFLOAT2(0.0f, 1.0f);
  vertices[0].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

  vertices[1].position = XMFLOAT3(0.0f, 1.0f, 0.0f);  // Top middle.
  vertices[1].texture = XMFLOAT2(0.5f, 0.0f);
  vertices[1].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

  vertices[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
  vertices[2].texture = XMFLOAT2(1.0f, 1.0f);
  vertices[2].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

  // Load the index array with data.
  indices[0] = 0;  // Bottom left.
  indices[1] = 1;  // Top middle.
  indices[2] = 2;  // Bottom right.

  // Set up the description of the static vertex buffer.
  D3D11_BUFFER_DESC vertexBufferDesc;
  vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  vertexBufferDesc.ByteWidth = sizeof(VertexType) * d_vertexCount;
  vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  vertexBufferDesc.CPUAccessFlags = 0;
  vertexBufferDesc.MiscFlags = 0;
  vertexBufferDesc.StructureByteStride = 0;

  // Give the subresource structure a pointer to the vertex data.
  D3D11_SUBRESOURCE_DATA vertexData;
  vertexData.pSysMem = vertices;
  vertexData.SysMemPitch = 0;
  vertexData.SysMemSlicePitch = 0;

  // Now create the vertex buffer.
  HRESULT result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &d_vertexBuffer);
  if (FAILED(result))
    return false;

  // Set up the description of the static index buffer.
  D3D11_BUFFER_DESC indexBufferDesc;
  indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  indexBufferDesc.ByteWidth = sizeof(unsigned long) * d_indexCount;
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  indexBufferDesc.CPUAccessFlags = 0;
  indexBufferDesc.MiscFlags = 0;
  indexBufferDesc.StructureByteStride = 0;

  // Give the subresource structure a pointer to the index data.
  D3D11_SUBRESOURCE_DATA indexData;
  indexData.pSysMem = indices;
  indexData.SysMemPitch = 0;
  indexData.SysMemSlicePitch = 0;

  // Create the index buffer.
  result = device->CreateBuffer(&indexBufferDesc, &indexData, &d_indexBuffer);
  if (FAILED(result))
    return false;

  // Release the arrays now that the vertex and index buffers have been created and loaded.
  delete[] vertices;
  vertices = 0;

  delete[] indices;
  indices = 0;

  return true;
}

bool ModelClass::LoadTexture(ID3D11Device* device, const std::wstring& filename)
{
  bool result;

  // Create the texture object.
  d_Texture = new TextureClass;
  if (!d_Texture)
    return false;

  // Initialize the texture object.
  result = d_Texture->Initialize(device, filename);
  if (!result)
    return false;

  return true;
}

void ModelClass::ReleaseTexture()
{
  // Release the texture object.
  if (d_Texture)
  {
    d_Texture->Shutdown();
    delete d_Texture;
    d_Texture = 0;
  }

  return;
}

void ModelClass::ShutdownBuffers()
{
  // Release the index buffer.
  if (d_indexBuffer)
  {
    d_indexBuffer->Release();
    d_indexBuffer = 0;
  }

  // Release the vertex buffer.
  if (d_vertexBuffer)
  {
    d_vertexBuffer->Release();
    d_vertexBuffer = 0;
  }

  return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
  // Set vertex buffer stride and offset.
  unsigned int stride = sizeof(VertexType);
  unsigned int offset = 0;

  // Set the vertex buffer to active in the input assembler so it can be rendered.
  deviceContext->IASetVertexBuffers(0, 1, &d_vertexBuffer, &stride, &offset);

  // Set the index buffer to active in the input assembler so it can be rendered.
  deviceContext->IASetIndexBuffer(d_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

  // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
  deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
