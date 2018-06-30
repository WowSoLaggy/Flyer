#include "stdafx.h"
#include "App.h"

#include "WindowsApi.h"

#include <Engine/IEngine.h>


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
}

void App::runEngine()
{
  d_pEngine = IEngine::createEngine();
  d_pEngine->run(
    std::bind(&App::controlCallback, std::ref(*this)),
    std::bind(&App::updateCallback, std::ref(*this), std::placeholders::_1));
}

void App::dispose()
{
  d_pEngine->disposeRenderer();
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
  
  return ControlSignal::Run;
}

void App::updateCallback(double i_dt)
{
}
