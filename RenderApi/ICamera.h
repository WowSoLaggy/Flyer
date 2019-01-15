#pragma once

#include <Sdk/SdkFwd.h>


class ICamera
{
public:

  static std::shared_ptr<ICamera> createCamera(int i_screenWidth, int i_screenHeight);

public:

  virtual ~ICamera() = default;

  virtual Vector3 getPosition() const = 0;
  virtual Vector3 getLookAt() const = 0;
  virtual Vector3 getUp() const = 0;

  virtual void setPosition(const Vector3& i_position) = 0;
  virtual void setLookAt(Vector3 i_direction) = 0;
  virtual void setUp(Vector3 i_up) = 0;

  virtual Vector3 getLeft() const = 0;
  virtual Vector3 getRight() const = 0;
  virtual Vector3 getForward() const = 0;
  virtual Vector3 getBackward() const = 0;

  virtual Vector2 worldToScreen(const Vector3& i_point) const = 0;
};
