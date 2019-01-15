#pragma once

#include "ICamera.h"

#include <Sdk/Vector.h>


class Camera : public ICamera
{
public:

  Camera(int i_screenWidth, int i_screenHeight);

  virtual float getYaw() const override { return d_yaw; }
  virtual void setYaw(float i_yaw) override;

  virtual float getPitch() const override { return d_pitch; }
  virtual void setPitch(float i_pitch) override;

  virtual float getDistance() const override { return d_distance; }
  virtual void setDistance(float i_distance) override;

  virtual Vector3 getLookAt() const override { return d_lookAt; }
  virtual void setLookAt(Vector3 i_lookAt) override;

  virtual Vector3 getUp() const override { return d_up; }
  virtual void setUp(Vector3 i_up) override;

  virtual Vector3 getLeft() const override;
  virtual Vector3 getRight() const override;
  virtual Vector3 getForward() const override;
  virtual Vector3 getBackward() const override;

  virtual Vector2 worldToScreen(const Vector3& i_point) const override;

  const XMMATRIX& getProjectionMatrix() const { return d_projectionMatrix; }
  const XMMATRIX& getViewMatrix() const { return d_viewMatrix; }

private:

  const float FovAngle = (float)DirectX::XM_PI / 4.0f;
  const float ViewportMinZ = 0.1f;
  const float ViewportMaxZ = 1000.0f;

  int d_viewportWidth;
  int d_viewportHeight;

  float d_yaw;
  float d_pitch;
  float d_distance;
  Vector3 d_lookAt;
  Vector3 d_up;

  XMMATRIX d_projectionMatrix;
  XMMATRIX d_viewMatrix;

  void updateProjectionMatrix();
  void updateViewMatrix();

  Vector3 getPosition() const;

};
