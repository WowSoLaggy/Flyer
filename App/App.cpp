#include "stdafx.h"
#include "App.h"

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

  d_engine = IEngine::create();
  d_engine->initialize(d_settingsController.getResourceFolder());
}

void App::runEngine()
{
  d_engine->run(
    std::bind(&App::controlCallback, std::ref(*this)),
    std::bind(&App::updateCallback, std::ref(*this), std::placeholders::_1),
    std::bind(&App::renderCallback, std::ref(*this)),
    std::bind(&App::inputCallback, std::ref(*this), std::placeholders::_1, std::placeholders::_2));
}

void App::dispose()
{
  d_engine->dispose();
  d_engine.reset();

  d_windowCreator.disposeWindow();
}
