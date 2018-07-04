#pragma once

#include "RenderApiFwd.h"


class Renderer
{
public:

  Renderer(
    const IRenderDevice& i_renderDevice,
    const IResourceController& i_resourceController,
    const ICamera& i_camera);

  void renderObject(const IObject3D& i_object);

private:

  const IRenderDevice& d_renderDevice;
  const IResourceController& d_resourceController;
  const ICamera& d_camera;

};
