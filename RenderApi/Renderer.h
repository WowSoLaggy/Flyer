#pragma once

#include "IRenderer.h"
#include "RenderApiFwd.h"


class Renderer : public IRenderer
{
public:

  Renderer(
    IRenderDevice& io_renderDevice,
    const IResourceController& i_resourceController,
    const ICamera& i_camera);

  virtual void renderObject(const IObject3D& i_object) override;

private:

  IRenderDevice& d_renderDevice;
  const IResourceController& d_resourceController;
  const ICamera& d_camera;

};
