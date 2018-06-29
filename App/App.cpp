#include "stdafx.h"
#include "App.h"

#include "WindowsApi.h"

#include <Engine/Engine.h>


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
  Engine engine;
  engine.run(
    std::bind(&App::controlCallback, *this),
    std::bind(&App::updateCallback, *this, std::placeholders::_1));
}

void App::dispose()
{
  d_windowCreator.disposeWindow();
}


ControlSignal App::controlCallback()
{
  return winPeekExit() ? ControlSignal::Stop : ControlSignal::Run;
}

void App::updateCallback(double i_dt)
{
}
