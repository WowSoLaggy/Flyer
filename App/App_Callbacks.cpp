#include "stdafx.h"
#include "App.h"

#include <Engine/IEngine.h>
#include <InputApi/KeyboardState.h>
#include <ModelControllers/WorldController.h>
#include <RenderApi/ICamera.h>
#include <ViewModel/WorldVm.h>


ControlSignal App::controlCallback()
{
  if (d_stopFlag)
    return ControlSignal::Stop;

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

void App::inputCallback(double i_dt, const KeyboardState& i_keyboardState)
{
  if (i_keyboardState.Escape)
  {
    stop();
    return;
  }

  const float speedMultiplier = i_keyboardState.LeftShift ? 60.f : 20.f;
  const float speed = (float)(speedMultiplier * i_dt);

  auto& camera = d_worldVm->getCamera();

  if (i_keyboardState.W)
  {
    auto dir = camera.getForward();
    dir.z = 0;
    camera.setPosition(camera.getPosition() + normalize(dir) * speed);
  }
  if (i_keyboardState.S)
  {
    auto dir = camera.getBackward();
    dir.z = 0;
    camera.setPosition(camera.getPosition() + normalize(dir) * speed);
  }
  if (i_keyboardState.A)
  {
    auto dir = camera.getLeft();
    dir.z = 0;
    camera.setPosition(camera.getPosition() + normalize(dir) * speed);
  }
  if (i_keyboardState.D)
  {
    auto dir = camera.getRight();
    dir.z = 0;
    camera.setPosition(camera.getPosition() + normalize(dir) * speed);
  }
}
