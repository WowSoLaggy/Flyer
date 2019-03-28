#include "stdafx.h"
#include "App.h"

#include <Engine/IEngine.h>
#include <GuiController/GuiCreator.h>
#include <GuiController/Gui3dCreator.h>
#include <GuiController/IGuiController.h>
#include <ModelControllers/IWorldController.h>
#include <ModelControllers/WorldCreator.h>
#include <Sdk/Random.h>
#include <ViewModel/GameVm.h>


void App::run()
{
  initialize();
  runEngine();
  dispose();
}


void App::initialize()
{
  Random_NS::randomize();

  d_window.create(
    d_settingsController.getWindowWidth(),
    d_settingsController.getWindowHeight(),
    d_settingsController.getAppName());
  d_window.show();

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

  d_window.dispose();
}

void App::stop()
{
  d_stopFlag = true;
}

void App::createRenderer()
{
  d_engine->createRenderer(d_window.getHWnd(),
    d_settingsController.getWindowWidth(), d_settingsController.getWindowHeight());
}

void App::createWorld()
{
  d_world = WorldCreator::createNewWorld();
  d_worldController = IWorldController::create(*d_world);

  d_gameVm = std::make_shared<GameVm>(
    *d_engine->getRenderDevice(), *d_engine->getResourceController(),
    *d_worldController,
    d_settingsController.getWindowWidth(), d_settingsController.getWindowHeight());

  d_guiCollection = GuiCreator::create();
  d_gui3dCollection = Gui3dCreator::create();
  d_guiController = IGuiController::create(*d_guiCollection, *d_gui3dCollection,
                                           *d_worldController, d_gameVm->getCamera());
  d_gameVm->buildGuiVms(*d_guiController);
}
