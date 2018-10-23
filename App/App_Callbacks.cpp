#include "stdafx.h"
#include "App.h"

#include <Engine/IEngine.h>
#include <GuiController/GuiController.h>
#include <InputApi/KeyboardState.h>
#include <ModelControllers/WorldController.h>
#include <RenderApi/ICamera.h>
#include <RenderApi/IRenderDevice.h>
#include <Sdk/Vector.h>
#include <ViewModel/GameVm.h>


ControlSignal App::controlCallback()
{
  if (d_stopFlag)
    return ControlSignal::Stop;

  if (!handleMessages())
    return ControlSignal::Stop;

  if (!d_engine->isRendererCreated())
    createRenderer();

  if (!d_world)
    createWorld();

  return ControlSignal::Run;
}

void App::updateCallback(double i_dt)
{
  WorldController::updateWorld(*d_world, i_dt);
  GuiController::update(d_guiCollection, i_dt);
}

void App::renderCallback(double i_dt)
{
  d_gameVm->render(i_dt);
}

void App::inputCallback(double i_dt, const KeyboardState& i_keyboardState)
{
  if (i_keyboardState.pressed.Escape)
  {
    stop();
    return;
  }

  const float speedMultiplier = i_keyboardState.currentState.LeftShift ? 60.f : 20.f;
  const float speed = (float)(speedMultiplier * i_dt);

  auto& camera = d_gameVm->getCamera();

  if (i_keyboardState.currentState.W)
  {
    auto dir = camera.getForward();
    dir.y = 0;
    camera.setPosition(camera.getPosition() + normalize(dir) * speed);
  }
  if (i_keyboardState.currentState.S)
  {
    auto dir = camera.getBackward();
    dir.y = 0;
    camera.setPosition(camera.getPosition() + normalize(dir) * speed);
  }
  if (i_keyboardState.currentState.A)
  {
    auto dir = camera.getLeft();
    dir.y = 0;
    camera.setPosition(camera.getPosition() + normalize(dir) * speed);
  }
  if (i_keyboardState.currentState.D)
  {
    auto dir = camera.getRight();
    dir.y = 0;
    camera.setPosition(camera.getPosition() + normalize(dir) * speed);
  }

  if (i_keyboardState.pressed.G && i_keyboardState.currentState.LeftControl)
  {
    d_engine->getRenderDevice()->switchFillMode();
  }
}
