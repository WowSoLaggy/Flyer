#pragma once

#include "ICamera.h"

#include <Sdk/Vector.h>


class Camera : public ICamera
{
public:

  Camera(int i_screenWidth, int i_screenHeight);

  virtual void setPosition(const Vector3& i_position) override;
  virtual void setDirection(const Vector3& i_direction) override;
  virtual void setUp(const Vector3& i_up) override;

  const XMMATRIX& getProjectionMatrix() const { return d_projectionMatrix; }
  const XMMATRIX& getViewMatrix() const { return d_viewMatrix; }

private:

  const float c_fovAngle = (float)DirectX::XM_PI / 4.0f;
  const float c_near = 0.1f;
  const float c_far = 100.0f;

  XMFLOAT3 d_position;
  XMFLOAT3 d_direction;
  XMFLOAT3 d_up;

  XMMATRIX d_projectionMatrix;
  XMMATRIX d_viewMatrix;

  void updateProjectionMatrix(int i_screenWidth, int i_screenHeight);
  void updateViewMatrix();

};
