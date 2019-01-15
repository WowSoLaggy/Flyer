#pragma once

#include "ICamera.h"

#include <Sdk/Vector.h>


class Camera : public ICamera
{
public:

  Camera(int i_screenWidth, int i_screenHeight);

  virtual Vector3 getPosition() const override;
  virtual Vector3 getLookAt() const override;
  virtual Vector3 getUp() const override;

  virtual void setPosition(const Vector3& i_position) override;
  virtual void setLookAt(Vector3 i_lookAt) override;
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

  XMFLOAT3 d_position;
  XMFLOAT3 d_lookAt;
  XMFLOAT3 d_up;

  XMMATRIX d_projectionMatrix;
  XMMATRIX d_viewMatrix;

  void updateProjectionMatrix();
  void updateViewMatrix();

};
