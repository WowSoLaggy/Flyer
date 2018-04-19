#pragma once

#include "Vector2.h"


class RenderDevice;


class GameObject
{
public:

  Vector2D position;

  void load(const RenderDevice& i_renderDevice);
  void unload();

};
