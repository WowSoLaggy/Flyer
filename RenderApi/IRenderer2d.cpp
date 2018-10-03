#include "stdafx.h"
#include "IRenderer2d.h"

#include "Renderer2d.h"


std::shared_ptr<IRenderer2d> IRenderer2d::create(
  IRenderDevice& io_renderDevice,
  const IResourceController& i_resourceController)
{
  return std::shared_ptr<IRenderer2d>(new Renderer2d(io_renderDevice, i_resourceController));
}
