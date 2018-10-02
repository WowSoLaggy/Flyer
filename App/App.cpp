#include "stdafx.h"
#include "App.h"

#include <Engine/IEngine.h>
#include <GuiController/GuiController.h>
#include <ModelControllers/WorldController.h>
#include <ViewModel/GuiCollectionVm.h>
#include <ViewModel/WorldVm.h>


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
    std::bind(&App::renderCallback, std::ref(*this)),
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
  d_world = WorldController::createNewWorld();

  d_worldVm = std::make_shared<WorldVm>(
    *d_engine->getRenderDevice(), *d_engine->getResourceController(),
    d_settingsController.getWindowWidth(), d_settingsController.getWindowHeight());

  d_worldVm->buildFromWorld(*d_world);

  
  d_guiCollection = GuiController::createGameGui();

  d_guiCollectionVm = std::make_shared<GuiCollectionVm>(
    *d_engine->getRenderDevice(), *d_engine->getResourceController());

  d_guiCollectionVm->buildFromCollection(*d_guiCollection);
}
