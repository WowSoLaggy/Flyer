#include "stdafx.h"
#include "App.h"

#include <Engine/IEngine.h>
#include <InputApi/KeyboardState.h>
#include <ModelControllers/WorldController.h>
#include <RenderApi/ICamera.h>
#include <ViewModel/WorldVm.h>


ControlSignal App::controlCallback()
{
  if (!handleMessages())
    return ControlSignal::Stop;

  if (!d_engine->isRendererCreated())
  {
    d_engine->createRenderer(d_windowCreator.getHWnd(),
      d_settingsController.getWindowWidth(), d_settingsController.getWindowHeight());
  }

  if (!d_world)
  {
    d_world = WorldController::createNewWorld();

    d_worldVm = std::make_shared<WorldVm>(
      *d_engine->getRenderDevice(), *d_engine->getResourceController(),
      d_settingsController.getWindowWidth(), d_settingsController.getWindowHeight());

    d_worldVm->buildFromWorld(*d_world);
  }

  return ControlSignal::Run;
}

void App::updateCallback(double i_dt)
{
  WorldController::updateWorld(*d_world, i_dt);
}

void App::renderCallback()
{
  d_worldVm->render();
}

