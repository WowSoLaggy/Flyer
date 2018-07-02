#pragma once

#include <Sdk/SdkFwd.h>


class ICamera
{
public:

  static std::shared_ptr<ICamera> createCamera(int i_screenWidth, int i_screenHeight);

public:

  virtual void setPosition(const Vector3& i_position) = 0;
  virtual void setDirection(const Vector3& i_direction) = 0;
  virtual void setUp(const Vector3& i_up) = 0;

};
