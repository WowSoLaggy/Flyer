#include "stdafx.h"
#include "GameVm.h"

#include "GuiCollectionVm.h"
#include "WorldVm.h"

#include <RenderApi/ICamera.h>
#include <RenderApi/IRenderer2d.h>
#include <RenderApi/IRenderer3d.h>
#include <Sdk/Math.h>


GameVm::GameVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController,
  int i_screenWidth, int i_screenHeight)
  : d_renderDevice(io_renderDevice)
  , d_resourceController(i_resourceController)
{
  d_camera = ICamera::createCamera(i_screenWidth, i_screenHeight);
  d_renderer2d = IRenderer2d::create(io_renderDevice, i_resourceController);
  d_renderer3d = IRenderer3d::create(io_renderDevice, i_resourceController, *d_camera);

  d_worldVm = std::make_shared<WorldVm>(io_renderDevice, i_resourceController);
  d_guiCollectionVm = std::make_shared<GuiCollectionVm>(io_renderDevice, i_resourceController);

  d_camera->setYaw(Math::degToRad(-90.0f));
  d_camera->setPitch(Math::degToRad(45.0f));
  d_camera->setDistance(20);

  d_camera->setLookAt({ 10, 1, 13 });
  d_camera->setUp({ 0, 1, 0 });
}


void GameVm::buildWorldVms(IWorldController& i_worldController)
{
  d_worldVm->buildFromWorld(i_worldController);
}

void GameVm::buildGuiVms(IGuiController& i_guiController)
{
  d_guiCollectionVm->buildFromCollection(i_guiController);
}


void GameVm::render(double i_dt) const
{
  d_renderer3d->beginScene();
  d_worldVm->render(*d_renderer3d, i_dt);
  d_renderer3d->endScene();

  d_renderer2d->beginScene();
  d_guiCollectionVm->render(*d_renderer2d, i_dt);
  d_renderer2d->endScene();
}
