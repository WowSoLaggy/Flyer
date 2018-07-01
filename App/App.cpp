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

  d_engine = IEngine::create();
  d_engine->initialize();
}

void App::runEngine()
{
  d_engine->run(
    std::bind(&App::controlCallback, std::ref(*this)),
    std::bind(&App::updateCallback, std::ref(*this), std::placeholders::_1));
}

void App::dispose()
{
  d_engine->dispose();
  d_engine.reset();

  d_windowCreator.disposeWindow();
}


ControlSignal App::controlCallback()
{
  if (winPeekExit())
    return ControlSignal::Stop;

  if (!d_engine->isRendererCreated())
  {
    d_engine->createRenderer(
      d_windowCreator.getHWnd(),
      d_settingsController.getWindowWidth(),
      d_settingsController.getWindowHeight());
  }

  if (!d_world)
    d_world = WorldController::createNewWorld();
  
  return ControlSignal::Run;
}

void App::updateCallback(double i_dt)
{
  WorldController::updateWorld(*d_world, i_dt);
}
