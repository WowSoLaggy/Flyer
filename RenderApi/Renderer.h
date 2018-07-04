#pragma once

#include "RenderApiFwd.h"


class Renderer
{
public:

  static void renderObject(
    const IRenderDevice& i_renderDevice, const ICamera& i_camera, const IObject& i_object);

};
