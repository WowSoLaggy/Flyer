#include "stdafx.h"
#include "Renderer.h"


void Renderer::renderObject(
  const IRenderDevice& i_renderDevice, const ICamera& i_camera, const IObject& i_object)
{
  unsigned int stride = sizeof(VertexTypePosTexNorm);
  unsigned int offset = 0;

  i_renderDevice.getDeviceContextPtr()->IASetVertexBuffers(0, 1, &d_vertexBuffer, &stride, &offset);
  i_renderDevice.getDeviceContextPtr()->IASetIndexBuffer(d_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

  i_renderDevice.getDeviceContextPtr()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  //i_renderable.renderBuffers(i_renderDevice);

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
