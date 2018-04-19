#pragma once


class Camera
{
public:

  void setPosition(XMFLOAT3 i_position);
  void setDirection(XMFLOAT3 i_direction);
  void setUp(XMFLOAT3 i_up);

  XMMATRIX getViewMatrix() const { return d_viewMatrix; }

private:

  XMFLOAT3 d_position = { 0.0f, 0.0f, 0.0f };
  XMFLOAT3 d_direction = { 1.0f, 0.0f, 0.0f };
  XMFLOAT3 d_up = { 0.0f, 0.0f, 1.0f };

  XMMATRIX d_viewMatrix;

  void updateViewMatrix();

};
