#pragma once

#include "RenderApiFwd.h"


class IRenderer
{
public:

  static std::shared_ptr<IRenderer> createRenderer(
    IRenderDevice& io_renderDevice,
    const IResourceController& i_resourceController,
    const ICamera& i_camera);

public:

  virtual ~IRenderer() = default;

  virtual void renderObject(const IObject3D& i_object) = 0;
};
