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

  Camera d_camera;
  DirectionalLight d_light;
  TextureLightShader d_textureLightShader;

  void initCamera(int i_screenWidth, int i_screenHeight);
  void initLight();

};
