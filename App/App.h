#pragma once

#include "SettingsController.h"
#include "WindowCreator.h"

#include <Engine/EngineFwd.h>


class App
{
public:

  void run();

private:

  std::shared_ptr<IEngine> d_pEngine;
  SettingsController d_settingsController;
  WindowCreator d_windowCreator;

  void initialize();
  void runEngine();
  void dispose();

  ControlSignal controlCallback();
  void updateCallback(double i_dt);

};
