#include "stdafx.h"
#include "App.h"

#include <Engine/IEngine.h>
#include <GuiController/GuiController.h>
#include <ModelControllers/WorldCreator.h>
#include <ViewModel/GameVm.h>


void App::run()
{
  initialize();
  runEngine();
  dispose();
}


void App::initialize()
{
  srand((unsigned int)time(nullptr));

  d_windowCreator.createWindow(
    d_settingsController.getWindowWidth(),
    d_settingsController.getWindowHeight(),
    d_settingsController.getAppName());
  d_windowCreator.showWindow();

  d_engine = IEngine::create();
  d_engine->initialize(d_settingsController.getResourceFolder());

  d_stopFlag = false;
}

void App::runEngine()
{
  d_engine->run(
    std::bind(&App::controlCallback, std::ref(*this)),
    std::bind(&App::updateCallback, std::ref(*this), std::placeholders::_1),
    std::bind(&App::renderCallback, std::ref(*this), std::placeholders::_1),
    std::bind(&App::inputCallback, std::ref(*this), std::placeholders::_1, std::placeholders::_2));
}

void App::dispose()
{
  d_engine->dispose();
  d_engine.reset();

  d_windowCreator.disposeWindow();
}

void App::stop()
{
  d_stopFlag = true;
}

void App::createRenderer()
{
  d_engine->createRenderer(d_windowCreator.getHWnd(),
    d_settingsController.getWindowWidth(), d_settingsController.getWindowHeight());
}

void App::createWorld()
{
  d_world = WorldCreator::createNewWorld();
  d_guiCollection = GuiController::createGameGui();

  d_gameVm = std::make_shared<GameVm>(
    *d_engine->getRenderDevice(), *d_engine->getResourceController(),
    d_settingsController.getWindowWidth(), d_settingsController.getWindowHeight());
  d_gameVm->buildWorldVms(*d_world);
  d_gameVm->buildGuiVms(*d_guiCollection);
}
