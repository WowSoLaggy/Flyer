#include "stdafx.h"
#include "IRenderer3d.h"

#include "Renderer3d.h"


std::shared_ptr<IRenderer3d> IRenderer3d::create(
  IRenderDevice& io_renderDevice,
  const IResourceController& i_resourceController,
  const ICamera& i_camera)
{
  return std::shared_ptr<IRenderer3d>(new Renderer3d(io_renderDevice, i_resourceController, i_camera));
}
