#include "stdafx.h"
#include "Drawer.h"

#include "RenderDevice.h"
#include "Map.h"


void Drawer::init()
{
  initCamera();
  initLight();
}


void Drawer::load(RenderDevice& i_renderDevice)
{
  initMatrices(i_renderDevice);
  d_textureLightShader.load(i_renderDevice);
}

void Drawer::unload()
{
  d_textureLightShader.unload();
}


void Drawer::draw(RenderDevice& i_renderDevice, const Map& i_map)
{
  i_renderDevice.beginScene();

  auto drawObject = [&](const IRenderable& i_renderable)
  {
    i_renderable.renderBuffers(i_renderDevice);

    d_textureLightShader.setParameters(i_renderDevice,
      d_identityMatrix, d_camera.getViewMatrix(), d_projectionMatrix,
      i_renderable.getTexture(), d_light.getDirection(), d_light.getColor());
    d_textureLightShader.render(i_renderDevice, i_renderable.getIndexCount());
  };

  i_map.render(i_renderDevice, drawObject);

  i_renderDevice.endScene();
}


void Drawer::initMatrices(RenderDevice& i_renderDevice)
{
  d_identityMatrix = XMMatrixIdentity();
  
  float screenAspect = (float)i_renderDevice.getScreenWidth() / (float)i_renderDevice.getScreenHeight();
  d_projectionMatrix = XMMatrixPerspectiveFovLH(c_fovAngle, screenAspect, c_near, c_far);
}

void Drawer::initCamera()
{
  d_camera.setPosition({ 0.0f, 20.0f, 20.0f });
  d_camera.setDirection({ 0.0f, -1.0f, -1.0f });
  d_camera.setUp({ 0.0f, 0.0f, 1.0f });
}

void Drawer::initLight()
{
  d_light.setDirection({ 0.0f, 0.0f, -1.0f });
  d_light.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
}
