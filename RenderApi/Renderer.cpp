#include "stdafx.h"
#include "Renderer.h"

#include "IObject3D.h"
#include "RenderDevice.h"
#include "ResourceController.h"


Renderer::Renderer(
  const IRenderDevice& i_renderDevice,
  const IResourceController& i_resourceController,
  const ICamera& i_camera)
  : d_renderDevice(i_renderDevice)
  , d_resourceController(i_resourceController)
  , d_camera(i_camera)
{
}


void Renderer::renderObject(const IObject3D& i_object3D)
{
  const auto& renderDevice = dynamic_cast<const RenderDevice&>(d_renderDevice);
  const auto& resourceController = dynamic_cast<const ResourceController&>(d_renderDevice);

  const auto& modelResource = resourceController.getModelResource(i_object3D.getModelResourceId());
  const auto& textureResource = resourceController.getTextureResource(i_object3D.getTextureResourceId());

  const auto position = i_object3D.getPosition();
  const auto& worldMatrix = XMMatrixTranslation(position.x, position.y, position.z);

  /*unsigned int stride = sizeof(VertexTypePosTexNorm);
  unsigned int offset = 0;

  renderDevice.getDeviceContextPtr()->IASetVertexBuffers(0, 1, &d_vertexBuffer, &stride, &offset);
  renderDevice.getDeviceContextPtr()->IASetIndexBuffer(d_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

  renderDevice.getDeviceContextPtr()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);*/

  //int curOffset = 0;
  //int numToDraw;
  //auto matSequence = i_renderable.getMaterialSequence();
  //for (int matIndex = 0; matIndex < matSequence.frameToMaterialPairs.size(); ++matIndex)
  //{
  //  Material& material = matSequence.frameToMaterialPairs[matIndex].second;
  //  if (matIndex == matSequence.frameToMaterialPairs.size() - 1)
  //  {
  //    // Last material to render
  //    numToDraw = i_renderable.getIndexCount() - curOffset;
  //  }
  //  else
  //    numToDraw = matSequence.frameToMaterialPairs[matIndex + 1].first - curOffset;

  //  d_textureLightShader.setParameters(i_renderDevice,
  //    i_renderable.getWorldMatrix(), d_camera.getViewMatrix(), d_camera.getProjectionMatrix(),
  //    i_renderable.getTexture(), d_light, material);

  //  d_textureLightShader.render(i_renderDevice, curOffset, numToDraw);
  //}
}
