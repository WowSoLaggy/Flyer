#include "stdafx.h"
#include "Drawer.h"


void Drawer::drawObject(const ICamera& i_camera)
{
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
