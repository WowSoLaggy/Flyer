#include "stdafx.h"
#include "Drawer.h"

#include "RenderDevice.h"
#include "Map.h"


void Drawer::init()
{
  initLight();
}


void Drawer::load(RenderDevice& i_renderDevice)
{
  initCamera(i_renderDevice.getScreenWidth(), i_renderDevice.getScreenHeight());
  d_textureLightShader.load(i_renderDevice);
}

void Drawer::unload()
{
  d_textureLightShader.unload();
}


void Drawer::draw(RenderDevice& i_renderDevice,
  const ResourceController& i_resourceController, const Map& i_map)
{
  i_renderDevice.beginScene();

  auto drawObject = [&](const IRenderable& i_renderable)
  {
    i_renderable.renderBuffers(i_renderDevice);

    int curOffset = 0;
    int numToDraw;
    auto matSequence = i_renderable.getMaterialSequence();
    for (int matIndex = 0; matIndex < matSequence.frameToMaterialPairs.size(); ++matIndex)
    {
      Material& material = matSequence.frameToMaterialPairs[matIndex].second;
      if (matIndex == matSequence.frameToMaterialPairs.size() - 1)
      {
        // Last material to render
        numToDraw = i_renderable.getIndexCount() - curOffset;
      }
      else
        numToDraw = matSequence.frameToMaterialPairs[matIndex + 1].first - curOffset;

      d_textureLightShader.setParameters(i_renderDevice,
        i_renderable.getWorldMatrix(), d_camera.getViewMatrix(), d_camera.getProjectionMatrix(),
        i_renderable.getTexture(), d_light, material);

      d_textureLightShader.render(i_renderDevice, curOffset, numToDraw);
    }
  };

  i_map.render(i_renderDevice, drawObject);

  i_renderDevice.endScene();
}


void Drawer::initCamera(int i_screenWidth, int i_screenHeight)
{
  d_camera.init(i_screenWidth, i_screenHeight);
  d_camera.setPosition({ 0.0f, 20.0f, 20.0f });
  d_camera.setDirection({ 0.0f, -1.0f, -1.0f });
  d_camera.setUp({ 0.0f, 0.0f, 1.0f });
}

void Drawer::initLight()
{
  d_light.setAmbientPower(0.2f);
  d_light.setDirection({ 0.0f, 0.0f, -1.0f });
  d_light.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
}
