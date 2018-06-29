#pragma once

#include "SettingsController.h"
#include "WindowCreator.h"

#include <Engine/Callbacks.h>


class App
{
public:

  void run();

private:

  SettingsController d_settingsController;
  WindowCreator d_windowCreator;

  void initialize();
  void runEngine();
  void dispose();

  ControlSignal controlCallback();
  void updateCallback(double i_dt);

};
