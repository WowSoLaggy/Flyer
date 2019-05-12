#include "stdafx.h"
#include "GameVm.h"

#include "GuiCollectionVm.h"
#include "WorldVm.h"

#include <Model/Creature.h>
#include <ModelControllers/WorldController.h>
#include <LaggyDx/ICamera.h>
#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IRenderer3d.h>
#include <LaggySdk/Math.h>


GameVm::GameVm(Dx::IRenderDevice& io_renderDevice, const Dx::IResourceController& i_resourceController,
               IWorldController& i_worldController,
               int i_screenWidth, int i_screenHeight)
  : d_renderDevice(io_renderDevice)
  , d_resourceController(i_resourceController)
  , d_worldController(dynamic_cast<WorldController&>(i_worldController))
{
  d_camera = Dx::ICamera::createCamera(i_screenWidth, i_screenHeight);
  d_renderer2d = Dx::IRenderer2d::create(io_renderDevice, i_resourceController);
  d_renderer3d = Dx::IRenderer3d::create(io_renderDevice, i_resourceController, *d_camera);

  d_worldVm = std::make_shared<WorldVm>(io_renderDevice, i_resourceController);
  d_worldVm->buildFromWorld(d_worldController);

  d_guiCollectionVm = std::make_shared<GuiCollectionVm>(io_renderDevice, i_resourceController);

  d_camera->setYaw(Sdk::degToRad(-90.0f));
  d_camera->setPitch(Sdk::degToRad(45.0f));
  d_camera->setDistance(20);
  d_camera->setLookAt({ 10, 1, 13 });
  d_camera->setUp({ 0, 1, 0 });
}


void GameVm::buildGuiVms(IGuiController& i_guiController)
{
  d_guiCollectionVm->buildFromCollection(i_guiController);
}


void GameVm::update(double i_dt) const
{
  if (auto playerPtr = d_worldController.getPlayer())
  {
    // Move camera to the player
    d_camera->setLookAt(playerPtr->getPosition());
  }
}

void GameVm::render(double i_dt) const
{
  d_renderer3d->beginScene();
  d_worldVm->render(*d_renderer3d, i_dt);
  d_renderer3d->endScene();

  d_renderer2d->beginScene();
  d_guiCollectionVm->render(*d_renderer2d, *d_renderer3d, i_dt);
  d_renderer2d->endScene();
}
