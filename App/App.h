#pragma once

#include "SettingsController.h"
#include "WindowCreator.h"

#include <Engine/EngineFwd.h>
#include <GuiModel/GuiModelFwd.h>
#include <GuiController/GuiControllerFwd.h>
#include <InputApi/InputDeviceFwd.h>
#include <Model/ModelFwd.h>
#include <ModelControllers/ModelControllersFwd.h>
#include <ViewModel/ViewModelFwd.h>


class App
{
public:

  void run();

private:

  SettingsController d_settingsController;
  WindowCreator d_windowCreator;
  std::shared_ptr<IEngine> d_engine;

  std::shared_ptr<World> d_world;
  std::shared_ptr<IWorldController> d_worldController;
  std::shared_ptr<GuiCollection> d_guiCollection;
  std::shared_ptr<HudCollection> d_hudCollection;
  std::shared_ptr<IGuiController> d_guiController;

  std::shared_ptr<GameVm> d_gameVm;

  bool d_stopFlag;

  void initialize();
  void runEngine();
  void dispose();

  bool handleMessages();
  void createRenderer();
  void createWorld();

  void stop();

  ControlSignal controlCallback();
  void updateCallback(double i_dt);
  void renderCallback(double i_dt);
  void inputCallback(double i_dt, const KeyboardState& i_keyboardState);

};
