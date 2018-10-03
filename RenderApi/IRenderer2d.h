#pragma once

#include "RenderApiFwd.h"


class IRenderer2d
{
public:

  static std::shared_ptr<IRenderer2d> create(
    IRenderDevice& io_renderDevice,
    const IResourceController& i_resourceController);

public:

  virtual ~IRenderer2d() = default;

  virtual void beginScene() = 0;
  virtual void endScene() = 0;

  virtual void renderObject(const IObject2d& i_object2d) = 0;
};
