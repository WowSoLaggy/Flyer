#pragma once

#include "SettingsController.h"
#include "WindowCreator.h"

#include <Engine/Engine.h>


class App
{
public:

  void run();

private:

  Engine d_engine;
  SettingsController d_settingsController;
  WindowCreator d_windowCreator;

  void initialize();
  void runEngine();
  void dispose();

  ControlSignal controlCallback();
  void updateCallback(double i_dt);

};
