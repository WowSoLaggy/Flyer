#include "stdafx.h"
#include "IRenderer.h"

#include "Renderer.h"


std::shared_ptr<IRenderer> IRenderer::createRenderer(
  IRenderDevice& io_renderDevice,
  const IResourceController& i_resourceController,
  const ICamera& i_camera)
{
  return std::shared_ptr<IRenderer>(new Renderer(io_renderDevice, i_resourceController, i_camera));
}
