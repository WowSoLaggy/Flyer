#include "stdafx.h"
#include "App.h"

#include "WindowsApi.h"

#include <Engine/IEngine.h>
#include <ModelControllers/WorldController.h>


void App::run()
{
  initialize();
  runEngine();
  dispose();
}


void App::initialize()
{
  d_windowCreator.createWindow(
    d_settingsController.getWindowWidth(),
    d_settingsController.getWindowHeight(),
    d_settingsController.getAppName());
  d_windowCreator.showWindow();

  d_pEngine = IEngine::create();
  d_pEngine->initialize();
}

void App::runEngine()
{
  d_pEngine->run(
    std::bind(&App::controlCallback, std::ref(*this)),
    std::bind(&App::updateCallback, std::ref(*this), std::placeholders::_1));
}

void App::dispose()
{
  d_pEngine->dispose();
  d_pEngine.reset();

  d_windowCreator.disposeWindow();
}


ControlSignal App::controlCallback()
{
  if (winPeekExit())
    return ControlSignal::Stop;

  if (!d_pEngine->isRendererCreated())
  {
    d_pEngine->createRenderer(
      d_windowCreator.getHWnd(),
      d_settingsController.getWindowWidth(),
      d_settingsController.getWindowHeight());
  }

  if (!d_pWorld)
    d_pWorld = WorldController::createNewWorld();
  
  return ControlSignal::Run;
}

void App::updateCallback(double i_dt)
{
  WorldController::updateWorld(*d_pWorld, i_dt);
}
