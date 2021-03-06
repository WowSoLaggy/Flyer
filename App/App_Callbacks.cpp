#include "stdafx.h"
#include "App.h"

#include <Engine/IEngine.h>
#include <GuiController/GuiController.h>
#include <LaggyDx/KeyboardState.h>
#include <LaggyDx/ICamera.h>
#include <LaggyDx/IRenderDevice.h>
#include <LaggySdk/HandleMessages.h>
#include <LaggySdk/Math.h>
#include <LaggySdk/Vector.h>
#include <ModelControllers/WorldController.h>
#include <ViewModel/GameVm.h>


ControlSignal App::controlCallback()
{
  if (d_stopFlag)
    return ControlSignal::Stop;

  if (!handleMessages(std::bind(&IEngine::processMessage, std::ref(*d_engine), std::placeholders::_1)))
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
  d_gameVm->update(i_dt);
  d_gameVm->render(i_dt);
}

void App::inputCallback(double i_dt, const Dx::KeyboardState& i_keyboardState)
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

  if (i_keyboardState.currentState.OemQuotes)
    camera.setYaw(camera.getYaw() + angleSpeed);
  if (i_keyboardState.currentState.L)
    camera.setYaw(camera.getYaw() - angleSpeed);
  if (i_keyboardState.currentState.N)
    camera.setYaw(Sdk::degToRad(-90.0f));
  if (i_keyboardState.currentState.P)
  {
    const float maxPitch = Sdk::degToRad(80.0f);
    float newPitch = std::min(camera.getPitch() + angleSpeed, maxPitch);
    camera.setPitch(newPitch);
  }
  if (i_keyboardState.currentState.OemSemicolon)
  {
    const float minPitch = Sdk::degToRad(5.0f);
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

  d_worldController->processInput(i_keyboardState);

  if (i_keyboardState.currentState.LeftControl)
  {
    if (i_keyboardState.pressed.G)
      d_engine->getRenderDevice()->switchFillMode();
    if (i_keyboardState.pressed.C)
      d_guiController->switchShowCollisionShapes();
  }
}
