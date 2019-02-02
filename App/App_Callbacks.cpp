#include "stdafx.h"
#include "App.h"

#include <Engine/IEngine.h>
#include <GuiController/GuiController.h>
#include <InputApi/KeyboardState.h>
#include <ModelControllers/WorldController.h>
#include <RenderApi/ICamera.h>
#include <RenderApi/IRenderDevice.h>
#include <Sdk/Math.h>
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
  d_worldController->update(i_dt);
  d_guiController->update(i_dt);
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

  const float linearSpeedMultiplier = i_keyboardState.currentState.LeftShift ? 60.f : 20.f;
  const float linearSpeed = (float)(linearSpeedMultiplier * i_dt);
  const float angleSpeedMultiplier = i_keyboardState.currentState.LeftShift ? 6.f : 2.f;
  const float angleSpeed = (float)(angleSpeedMultiplier * i_dt);

  auto& camera = d_gameVm->getCamera();

  if (i_keyboardState.currentState.W)
  {
    auto dir = camera.getForward();
    dir.y = 0;
    camera.setLookAt(camera.getLookAt() + normalize(dir) * linearSpeed);
  }
  if (i_keyboardState.currentState.S)
  {
    auto dir = camera.getBackward();
    dir.y = 0;
    camera.setLookAt(camera.getLookAt() + normalize(dir) * linearSpeed);
  }
  if (i_keyboardState.currentState.A)
  {
    auto dir = camera.getLeft();
    dir.y = 0;
    camera.setLookAt(camera.getLookAt() + normalize(dir) * linearSpeed);
  }
  if (i_keyboardState.currentState.D)
  {
    auto dir = camera.getRight();
    dir.y = 0;
    camera.setLookAt(camera.getLookAt() + normalize(dir) * linearSpeed);
  }

  if (i_keyboardState.currentState.OemQuotes)
    camera.setYaw(camera.getYaw() + angleSpeed);
  if (i_keyboardState.currentState.L)
    camera.setYaw(camera.getYaw() - angleSpeed);
  if (i_keyboardState.currentState.N)
    camera.setYaw(Math::degToRad(-90.0f));
  if (i_keyboardState.currentState.P)
  {
    const float maxPitch = Math::degToRad(80.0f);
    float newPitch = std::min(camera.getPitch() + angleSpeed, maxPitch);
    camera.setPitch(newPitch);
  }
  if (i_keyboardState.currentState.OemSemicolon)
  {
    const float minPitch = Math::degToRad(5.0f);
    float newPitch = std::max(camera.getPitch() - angleSpeed, minPitch);
    camera.setPitch(newPitch);
  }
  if (i_keyboardState.currentState.OemOpenBrackets)
  {
    const float maxDistance = 30.0f;
    float newDistance = std::min(camera.getDistance() + linearSpeed, maxDistance);
    camera.setDistance(newDistance);
  }
  if (i_keyboardState.currentState.OemCloseBrackets)
  {
    const float minDistance = 3.0f;
    float newDistance = std::max(camera.getDistance() - linearSpeed, minDistance);
    camera.setDistance(newDistance);
  }

  if (i_keyboardState.currentState.LeftControl)
  {
    if (i_keyboardState.pressed.G)
      d_engine->getRenderDevice()->switchFillMode();
  }
}
