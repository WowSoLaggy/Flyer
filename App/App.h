#pragma once

#include "SettingsController.h"

#include <Engine/EngineFwd.h>
#include <GuiModel/GuiModelFwd.h>
#include <GuiController/GuiControllerFwd.h>
#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/Window.h>
#include <Model/ModelFwd.h>
#include <ModelControllers/ModelControllersFwd.h>
#include <ViewModel/ViewModelFwd.h>


class App
{
public:

  void run();

private:

  SettingsController d_settingsController;
  Sdk::Window d_window;
  std::shared_ptr<IEngine> d_engine;

  std::shared_ptr<World> d_world;
  std::shared_ptr<IWorldController> d_worldController;
  std::shared_ptr<GuiCollection> d_guiCollection;
  std::shared_ptr<Gui3dCollection> d_gui3dCollection;
  std::shared_ptr<IGuiController> d_guiController;

  std::shared_ptr<GameVm> d_gameVm;

  bool d_stopFlag;

  void initialize();
  void runEngine();
  void dispose();

  void createRenderer();
  void createWorld();

  void stop();

  ControlSignal controlCallback();
  void updateCallback(double i_dt);
  void renderCallback(double i_dt);
  void inputCallback(double i_dt, const Dx::KeyboardState& i_keyboardState);

};
