#pragma once


class SettingsController
{
public:
  SettingsController() = delete;

  static std::string getAppName();

  static int getWindowWidth();
  static int getWindowHeight();
};
