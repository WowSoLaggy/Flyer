#include "stdafx.h"
#include "WorldVm.h"

#include <Model/World.h>
#include <RenderApi/ICamera.h>
#include <RenderApi/IRenderer.h>


WorldVm::WorldVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController,
  int i_screenWidth, int i_screenHeight)
  : d_renderDevice(io_renderDevice)
  , d_resourceController(i_resourceController)
{
  d_camera = ICamera::createCamera(i_screenWidth, i_screenHeight);
  d_renderer = IRenderer::createRenderer(io_renderDevice, i_resourceController, *d_camera);
}


void WorldVm::buildFromWorld(const World& i_world)
{
  d_terrainVm = std::shared_ptr<TerrainVm>(new TerrainVm(d_resourceController, i_world.getTerrain()));

  for (const auto& object : i_world.getObjects())
    d_objectVms.push_back({ d_resourceController, object });
}


void WorldVm::render() const
{
  d_renderer->renderObject(*d_terrainVm);

  for (const auto& objectVm : d_objectVms)
    d_renderer->renderObject(objectVm);
}
