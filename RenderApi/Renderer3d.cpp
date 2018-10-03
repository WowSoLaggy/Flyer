#include "stdafx.h"
#include "Renderer3d.h"

#include "Camera.h"
#include "IObject3d.h"
#include "MeshResource.h"
#include "PixelShaderResource.h"
#include "RenderDevice.h"
#include "ResourceController.h"
#include "ShaderBuffers.h"
#include "TextureResource.h"
#include "VertexShaderResource.h"


Renderer3d::Renderer3d(
  IRenderDevice& io_renderDevice,
  const IResourceController& i_resourceController,
  const ICamera& i_camera)
  : d_renderDevice(io_renderDevice)
  , d_resourceController(i_resourceController)
  , d_camera(i_camera)
{
  createBuffers();
}

Renderer3d::~Renderer3d()
{
  disposeBuffers();
}


void Renderer3d::renderObject(const IObject3d& i_object3d)
{
  auto& renderDevice = dynamic_cast<RenderDevice&>(d_renderDevice);
  const auto& resourceController = dynamic_cast<const ResourceController&>(d_resourceController);

  const auto& meshResource = resourceController.getMeshResource(i_object3d.getMeshResourceId());
  const auto& textureResource = resourceController.getTextureResource(i_object3d.getTextureResourceId());

  setShaders();
  
  setBuffers(
    meshResource.getVertexBuffer().getPtr(), meshResource.getIndexBuffer().getPtr(),
    unsigned int(meshResource.getVertexBuffer().getStride()));

  
  setShaderMatrices(i_object3d.getPosition());
  setShaderTexture(textureResource.getTexturePtr());


  const auto& materialSpans = meshResource.getMaterialSpans();
  for (auto& materialSpan : materialSpans)
    drawMaterial(materialSpan);
}


void Renderer3d::setBuffers(ID3D11Buffer* i_vertexBufferPtr, ID3D11Buffer* i_indexBufferPtr, unsigned int i_stride)
{
  auto& renderDevice = dynamic_cast<RenderDevice&>(d_renderDevice);

  unsigned int offset = 0;
  renderDevice.getDeviceContextPtr()->IASetVertexBuffers(0, 1, &i_vertexBufferPtr, &i_stride, &offset);
  renderDevice.getDeviceContextPtr()->IASetIndexBuffer(i_indexBufferPtr, DXGI_FORMAT_R32_UINT, 0);

  renderDevice.getDeviceContextPtr()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Renderer3d::setShaders()
{
  auto& renderDevice = dynamic_cast<RenderDevice&>(d_renderDevice);
  const auto& resourceController = dynamic_cast<const ResourceController&>(d_resourceController);

  auto pixelShaderResourceId = resourceController.getResourceId("TextureLightPS.ps");
  auto vertexShaderResourceId = resourceController.getResourceId("TextureLightVS.vs");

  const auto& pixelShaderResource = resourceController.getPixelShaderResource(pixelShaderResourceId);
  const auto& vertexShaderResource = resourceController.getVertexShaderResource(vertexShaderResourceId);
  
  auto* samplerState = pixelShaderResource.getSampleStatePtr();

  renderDevice.getDeviceContextPtr()->IASetInputLayout(vertexShaderResource.getLayoutPtr());
  renderDevice.getDeviceContextPtr()->VSSetShader(vertexShaderResource.getPtr(), nullptr, 0);
  renderDevice.getDeviceContextPtr()->PSSetShader(pixelShaderResource.getPtr(), nullptr, 0);
  renderDevice.getDeviceContextPtr()->PSSetSamplers(0, 1, &samplerState);
}

void Renderer3d::setShaderMatrices(const Vector3& i_position)
{
  auto& renderDevice = dynamic_cast<RenderDevice&>(d_renderDevice);
  auto& camera = dynamic_cast<const Camera&>(d_camera);


  auto worldMatrix = XMMatrixTranspose(XMMatrixTranslation(i_position.x, i_position.y, i_position.z));
  auto viewMatrix = XMMatrixTranspose(camera.getViewMatrix());
  auto projectionMatrix = XMMatrixTranspose(camera.getProjectionMatrix());

  D3D11_MAPPED_SUBRESOURCE mappedResource;
  renderDevice.getDeviceContextPtr()->Map(d_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

  auto* dataPtr = (MatrixBuffer*)mappedResource.pData;
  dataPtr->world = worldMatrix;
  dataPtr->view = viewMatrix;
  dataPtr->projection = projectionMatrix;

  renderDevice.getDeviceContextPtr()->Unmap(d_matrixBuffer, 0);

  renderDevice.getDeviceContextPtr()->VSSetConstantBuffers(0, 1, &d_matrixBuffer);
}

void Renderer3d::setShaderTexture(ID3D11ShaderResourceView* i_texture)
{
  auto& renderDevice = dynamic_cast<RenderDevice&>(d_renderDevice);
  renderDevice.getDeviceContextPtr()->PSSetShaderResources(0, 1, &i_texture);
}

void Renderer3d::setShaderMaterial(const Material& i_material)
{
  auto& renderDevice = dynamic_cast<RenderDevice&>(d_renderDevice);

  D3D11_MAPPED_SUBRESOURCE mappedResource;
  renderDevice.getDeviceContextPtr()->Map(d_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

  auto* dataPtr2 = (LightBuffer*)mappedResource.pData;
  dataPtr2->diffuseColor = i_material.diffuseColor;
  dataPtr2->lightColor = { 1.0f, 1.0f, 1.0f, 1.0f };
  dataPtr2->lightDirection = { 0.0f, 0.0f, -1.0f };
  dataPtr2->ambientStrength = 0.2f;

  renderDevice.getDeviceContextPtr()->Unmap(d_lightBuffer, 0);

  renderDevice.getDeviceContextPtr()->PSSetConstantBuffers(0, 1, &d_lightBuffer);
}

void Renderer3d::drawMaterial(const MaterialSpan& i_materialSpan)
{
  auto& renderDevice = dynamic_cast<RenderDevice&>(d_renderDevice);

  setShaderMaterial(i_materialSpan.material);
  renderDevice.getDeviceContextPtr()->DrawIndexed(i_materialSpan.count, i_materialSpan.startIndex, 0);
}


void Renderer3d::createBuffers()
{
  auto& renderDevice = dynamic_cast<RenderDevice&>(d_renderDevice);

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

  renderDevice.getDevicePtr()->CreateBuffer(&matrixBufferDesc, nullptr, &d_matrixBuffer);
  renderDevice.getDevicePtr()->CreateBuffer(&lightBufferDesc, nullptr, &d_lightBuffer);
}

void Renderer3d::disposeBuffers()
{
  d_matrixBuffer->Release();
  d_lightBuffer->Release();
}


void Renderer3d::beginScene()
{
  auto& renderDevice = dynamic_cast<RenderDevice&>(d_renderDevice);
  renderDevice.resetBlendState();
}

void Renderer3d::endScene()
{
}
