#pragma once

#include "ICamera.h"

#include <Sdk/Vector.h>


class Camera : public ICamera
{
public:

  Camera(int i_screenWidth, int i_screenHeight);

  virtual Vector3 getPosition() const override;
  virtual Vector3 getDirection() const override;
  virtual Vector3 getUp() const override;

  virtual void setPosition(const Vector3& i_position) override;
  virtual void setDirection(Vector3 i_direction) override;
  virtual void setUp(Vector3 i_up) override;

  virtual Vector3 getLeft() const override;
  virtual Vector3 getRight() const override;
  virtual Vector3 getForward() const override;
  virtual Vector3 getBackward() const override;

  const XMMATRIX& getProjectionMatrix() const { return d_projectionMatrix; }
  const XMMATRIX& getViewMatrix() const { return d_viewMatrix; }

private:

  const float c_fovAngle = (float)DirectX::XM_PI / 4.0f;
  const float c_near = 0.1f;
  const float c_far = 1000.0f;

  XMFLOAT3 d_position;
  XMFLOAT3 d_direction;
  XMFLOAT3 d_up;

  XMMATRIX d_projectionMatrix;
  XMMATRIX d_viewMatrix;

  void updateProjectionMatrix(int i_screenWidth, int i_screenHeight);
  void updateViewMatrix();

};
