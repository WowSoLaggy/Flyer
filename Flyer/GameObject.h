#pragma once

class RenderDevice;


class GameObject
{
public:

  XMFLOAT3 position;

  void load(const RenderDevice& i_renderDevice);
  void unload();

};
