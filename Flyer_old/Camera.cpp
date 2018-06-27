#include "stdafx.h"
#include "Camera.h"


void Camera::init(int i_screenWidth, int i_screenHeight)
{
  float screenAspect = (float)i_screenWidth / (float)i_screenHeight;
  d_projectionMatrix = XMMatrixPerspectiveFovLH(c_fovAngle, screenAspect, c_near, c_far);

  d_position = { 0.0f, 0.0f, 0.0f };
  d_direction = { 1.0f, 0.0f, 0.0f };
  d_up = { 0.0f, 0.0f, 1.0f };
}


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
