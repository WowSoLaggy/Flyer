#pragma once


class SettingsController
{
public:

  std::string getAppName() const;

  int getWindowWidth() const;
  int getWindowHeight() const;

  std::string getResourceFolder() const;

};
