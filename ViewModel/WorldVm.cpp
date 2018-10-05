#include "stdafx.h"
#include "WorldVm.h"

#include "TerrainVm.h"
#include "ObjectVm.h"

#include <Model/World.h>
#include <RenderApi/ICamera.h>
#include <RenderApi/IRenderer3d.h>


WorldVm::WorldVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController,
  int i_screenWidth, int i_screenHeight)
  : d_renderDevice(io_renderDevice)
  , d_resourceController(i_resourceController)
{
  d_camera = ICamera::createCamera(i_screenWidth, i_screenHeight);
  d_renderer = IRenderer3d::create(io_renderDevice, i_resourceController, *d_camera);
}


void WorldVm::buildFromWorld(const World& i_world)
{
  const Vector3 defaultCameraOffset = { 10, 15, -10 };
  d_camera->setPosition(defaultCameraOffset);
  d_camera->setDirection({ 0, -1, 1 });
  d_camera->setUp({ 0, 1, 0 });

  d_terrainVm = std::shared_ptr<TerrainVm>(
    new TerrainVm(d_renderDevice, d_resourceController, i_world.getTerrain()));

  for (const auto& object : i_world.getObjects())
    d_objectVms.push_back(std::make_shared<ObjectVm>(d_resourceController, object));
}


void WorldVm::render() const
{
  d_renderer->beginScene();

  d_terrainVm->render(*d_renderer);

  for (const auto& objectVm : d_objectVms)
    objectVm->render(*d_renderer);

  d_renderer->endScene();
}
