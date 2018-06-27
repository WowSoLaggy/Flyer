#include "stdafx.h"
#include "Map.h"

#include "RenderDevice.h"
#include "VertexTypes.h"


void Map::load(RenderDevice& i_renderDevice, const ResourceController& i_resourceController)
{
  d_worldMatrix = XMMatrixIdentity();
  d_materialSequence = MaterialSequence::createBlank();

  loadBuffers(i_renderDevice);
  loadTexture(i_renderDevice);

  for (auto& object : d_objects)
    object.load(i_renderDevice, i_resourceController);
}

void Map::unload()
{
  for (auto& object : d_objects)
    object.unload();

  unloadTexture();
  unloadBuffers();
}


void Map::render(RenderDevice& i_renderDevice, RenderFunc i_renderFunc) const
{
  i_renderFunc(*this);

  for (auto& object : d_objects)
    i_renderFunc(object);
}

void Map::renderBuffers(RenderDevice& i_renderDevice) const
{
  unsigned int stride = sizeof(VertexTypePosTexNorm);
  unsigned int offset = 0;

  i_renderDevice.getDeviceContextPtr()->IASetVertexBuffers(0, 1, &d_vertexBuffer, &stride, &offset);
  i_renderDevice.getDeviceContextPtr()->IASetIndexBuffer(d_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

  i_renderDevice.getDeviceContextPtr()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}


void Map::loadBuffers(RenderDevice& i_renderDevice)
{
  std::vector<VertexTypePosTexNorm> vertices;

  vertices.push_back({
    XMFLOAT3(-c_width / 2.0f, -c_height / 2.0f, c_defaultTerrainHeight),
    XMFLOAT2(0.0f, 0.0f),
    XMFLOAT3(0.0f, 0.0f, 1.0f) });
  vertices.push_back({
    XMFLOAT3(c_width / 2.0f, -c_height / 2.0f, c_defaultTerrainHeight),
    XMFLOAT2(c_width / 2.0f, 0.0f),
    XMFLOAT3(0.0f, 0.0f, 1.0f) });
  vertices.push_back({
    XMFLOAT3(c_width / 2.0f, c_height / 2.0f, c_defaultTerrainHeight),
    XMFLOAT2(c_width / 2.0f, c_height / 2.0f),
    XMFLOAT3(0.0f, 0.0f, 1.0f) });
  vertices.push_back({
    XMFLOAT3(-c_width / 2.0f, c_height / 2.0f, c_defaultTerrainHeight),
    XMFLOAT2(0.0f, c_height / 2.0f),
    XMFLOAT3(0.0f, 0.0f, 1.0f) });

  std::vector<unsigned long> indices = { 0, 1, 2, 0, 2, 3 };
  d_indexCount = (int)indices.size();

  //

  D3D11_BUFFER_DESC vertexBufferDesc;
  vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  vertexBufferDesc.ByteWidth = sizeof(VertexTypePosTexNorm) * (unsigned int)vertices.size();
  vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  vertexBufferDesc.CPUAccessFlags = 0;
  vertexBufferDesc.MiscFlags = 0;
  vertexBufferDesc.StructureByteStride = 0;

  D3D11_BUFFER_DESC indexBufferDesc;
  indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  indexBufferDesc.ByteWidth = sizeof(unsigned long) * d_indexCount;
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  indexBufferDesc.CPUAccessFlags = 0;
  indexBufferDesc.MiscFlags = 0;
  indexBufferDesc.StructureByteStride = 0;

  D3D11_SUBRESOURCE_DATA vertexData;
  vertexData.pSysMem = vertices.data();
  vertexData.SysMemPitch = 0;
  vertexData.SysMemSlicePitch = 0;

  D3D11_SUBRESOURCE_DATA indexData;
  indexData.pSysMem = indices.data();
  indexData.SysMemPitch = 0;
  indexData.SysMemSlicePitch = 0;

  //

  i_renderDevice.getDevicePtr()->CreateBuffer(&vertexBufferDesc, &vertexData, &d_vertexBuffer);
  i_renderDevice.getDevicePtr()->CreateBuffer(&indexBufferDesc, &indexData, &d_indexBuffer);
}

void Map::loadTexture(RenderDevice& i_renderDevice)
{
  CreateDDSTextureFromFile(i_renderDevice.getDevicePtr(), c_textureName.c_str(), nullptr, &d_texture);
}


void Map::unloadBuffers()
{
  d_vertexBuffer->Release();
  d_indexBuffer->Release();
}

void Map::unloadTexture()
{
  d_texture->Release();
}
