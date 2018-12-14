#pragma once


class SettingsController
{
public:

  std::string getAppName() const;

  int getWindowWidth() const;
  int getWindowHeight() const;
  float getWindowAspect() const;

  std::string getResourceFolder() const;

};
