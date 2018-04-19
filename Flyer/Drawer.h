#pragma once

#include "Camera.h"
#include "DirectionalLight.h"
#include "TextureLightShader.h"

class RenderDevice;
class Map;


class Drawer
{
public:

  void init();

  void load(RenderDevice& i_renderDevice);
  void unload();

  void draw(RenderDevice& i_renderDevice, const Map& i_map);

private:

  const float c_fovAngle = (float)DirectX::XM_PI / 4.0f;
  const float c_near = 0.1f;
  const float c_far = 100.0f;

  Camera d_camera;
  DirectionalLight d_light;
  TextureLightShader d_textureLightShader;

  XMMATRIX d_identityMatrix;
  XMMATRIX d_projectionMatrix;

  void initMatrices(RenderDevice& i_renderDevice);
  void initCamera();
  void initLight();

};
