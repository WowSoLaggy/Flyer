#pragma once

#include "SettingsController.h"
#include "WindowCreator.h"

#include <Engine/EngineFwd.h>


class App
{
public:

  void run();

private:

  SettingsController d_settingsController;
  WindowCreator d_windowCreator;
  std::shared_ptr<IEngine> d_pEngine;

  void initialize();
  void runEngine();
  void dispose();

  ControlSignal controlCallback();
  void updateCallback(double i_dt);

};
