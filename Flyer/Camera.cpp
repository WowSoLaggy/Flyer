#include "stdafx.h"
#include "Camera.h"


void Camera::setPosition(XMFLOAT3 i_position)
{
  d_position = i_position;
  updateViewMatrix();
}

void Camera::setDirection(XMFLOAT3 i_direction)
{
  d_direction = i_direction;
  updateViewMatrix();
}

void Camera::setUp(XMFLOAT3 i_up)
{
  d_up = i_up;
  updateViewMatrix();
}


void Camera::updateViewMatrix()
{
  XMFLOAT3 lookAt = {
    d_position.x + d_direction.x,
    d_position.y + d_direction.y,
    d_position.z + d_direction.z };

  d_viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&d_position), XMLoadFloat3(&lookAt), XMLoadFloat3(&d_up));
}
