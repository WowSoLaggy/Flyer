#include "stdafx.h"
#include "ModelResource.h"

#include "MeshLoader.h"
#include "RenderDevice.h"
#include "Utils.h"
#include "VertexTypes.h"


ModelResource::ModelResource(const std::string& i_modelName)
  : d_modelName(i_modelName)
{
}


void ModelResource::load(RenderDevice& i_renderDevice)
{
  std::vector<VertexTypePosTexNorm> vertices;
  std::vector<int> indices;

  MeshLoader::loadMeshInfoFromFile(d_modelName + ".obj", d_modelName + ".mtl",
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

void ModelResource::unload()
{
  d_vertexBuffer->Release();
  d_indexBuffer->Release();
}


void ModelResource::setBuffersToRender(RenderDevice& i_renderDevice) const
{
  unsigned int stride = sizeof(VertexTypePosTexNorm);
  unsigned int offset = 0;

  i_renderDevice.getDeviceContextPtr()->IASetVertexBuffers(0, 1, &d_vertexBuffer, &stride, &offset);
  i_renderDevice.getDeviceContextPtr()->IASetIndexBuffer(d_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

  i_renderDevice.getDeviceContextPtr()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
