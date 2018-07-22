#pragma once

#include "SettingsController.h"
#include "WindowCreator.h"

#include <Engine/EngineFwd.h>
#include <Model/World.h>
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
  std::shared_ptr<WorldVm> d_worldVm;

  void initialize();
  void runEngine();
  void dispose();

  ControlSignal controlCallback();
  void updateCallback(double i_dt);
  void renderCallback();

};
