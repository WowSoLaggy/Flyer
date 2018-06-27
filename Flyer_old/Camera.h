#pragma once


class Camera
{
public:

  void init(int i_screenWidth, int i_screenHeight);

  void setPosition(XMFLOAT3 i_position);
  void setDirection(XMFLOAT3 i_direction);
  void setUp(XMFLOAT3 i_up);

  XMMATRIX getViewMatrix() const { return d_viewMatrix; }
  XMMATRIX getProjectionMatrix() const { return d_projectionMatrix; }

private:

  const float c_fovAngle = (float)DirectX::XM_PI / 4.0f;
  const float c_near = 0.1f;
  const float c_far = 100.0f;

  XMFLOAT3 d_position;
  XMFLOAT3 d_direction;
  XMFLOAT3 d_up;

  XMMATRIX d_viewMatrix;
  XMMATRIX d_projectionMatrix;

  void updateViewMatrix();

};
