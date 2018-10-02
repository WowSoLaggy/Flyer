#pragma once

#include "RenderApiFwd.h"


class IRenderer3d
{
public:

  static std::shared_ptr<IRenderer3d> create(
    IRenderDevice& io_renderDevice,
    const IResourceController& i_resourceController,
    const ICamera& i_camera);

public:

  virtual ~IRenderer3d() = default;

  virtual void renderObject(const IObject3d& i_object) = 0;
};
