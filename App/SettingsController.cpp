#include "stdafx.h"
#include "SettingsController.h"


std::string SettingsController::getAppName() const
{
  return "Glory of Rome";
}


int SettingsController::getWindowWidth() const
{
  return 1280;
}

int SettingsController::getWindowHeight() const
{
  return 960;
}

float SettingsController::getWindowAspect() const
{
  return (float)getWindowWidth() / (float)getWindowHeight();
}


std::string SettingsController::getResourceFolder() const
{
  return ".\\data\\";
}
