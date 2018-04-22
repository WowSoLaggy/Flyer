#include "stdafx.h"
#include "GameObject.h"

#include "MeshLoader.h"
#include "RenderDevice.h"
#include "VertexTypes.h"


void GameObject::setResourceNames(const std::wstring& i_modelName, const std::wstring& i_textureName)
{
  d_modelName = i_modelName;
  d_textureName = i_textureName;
}


void GameObject::load(RenderDevice& i_renderDevice)
{
  updateWorldMatrix();

  loadBuffers(i_renderDevice);
  loadTexture(i_renderDevice);
}

void GameObject::unload()
{
  unloadTexture();
  unloadBuffers();
}


void GameObject::render(RenderDevice& i_renderDevice, RenderFunc i_renderFunc) const
{
  i_renderFunc(*this);
}

void GameObject::renderBuffers(RenderDevice& i_renderDevice) const
{
  unsigned int stride = sizeof(VertexTypePosTexNorm);
  unsigned int offset = 0;

  i_renderDevice.getDeviceContextPtr()->IASetVertexBuffers(0, 1, &d_vertexBuffer, &stride, &offset);
  i_renderDevice.getDeviceContextPtr()->IASetIndexBuffer(d_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

  i_renderDevice.getDeviceContextPtr()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}


void GameObject::loadBuffers(RenderDevice& i_renderDevice)
{
  std::vector<VertexTypePosTexNorm> vertices;
  std::vector<int> indices;

  MeshLoader::loadMeshInfoFromFile(d_modelName + L".obj", d_modelName + L".mtl",
    vertices, indices, d_materialSequence);

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
  indexBufferDesc.ByteWidth = sizeof(int) * d_indexCount;
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

void GameObject::loadTexture(RenderDevice& i_renderDevice)
{
  CreateDDSTextureFromFile(i_renderDevice.getDevicePtr(), d_textureName.c_str(), nullptr, &d_texture);
}


void GameObject::unloadBuffers()
{
  d_vertexBuffer->Release();
  d_indexBuffer->Release();
}

void GameObject::unloadTexture()
{
  d_texture->Release();
}


void GameObject::setPosition(XMFLOAT3 i_position)
{
  d_position = i_position;
  updateWorldMatrix();
}

void GameObject::updateWorldMatrix()
{
  d_worldMatrix = XMMatrixTranslation(d_position.x, d_position.y, d_position.z);
}
