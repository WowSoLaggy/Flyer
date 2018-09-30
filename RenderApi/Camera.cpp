#include "stdafx.h"
#include "Camera.h"


Camera::Camera(int i_screenWidth, int i_screenHeight)
  : d_position{ 0, 0, 0 }
  , d_direction{ 1, 0, 0 }
  , d_up{ 0, 1, 0 }
{
  updateProjectionMatrix(i_screenWidth, i_screenHeight);
}


Vector3 Camera::getPosition() const
{
  return { d_position.x, d_position.y, d_position.z };
}

Vector3 Camera::getDirection() const
{
  return { d_direction.x, d_direction.y, d_direction.z };
}

Vector3 Camera::getUp() const
{
  return { d_up.x, d_up.y, d_up.z };
}


void Camera::setPosition(const Vector3& i_position)
{
  d_position = XMFLOAT3(i_position.x, i_position.y, i_position.z);
  updateViewMatrix();
}

void Camera::setDirection(Vector3 i_direction)
{
  i_direction = normalize(i_direction);
  d_direction = XMFLOAT3(i_direction.x, i_direction.y, i_direction.z);
  updateViewMatrix();
}

void Camera::setUp(Vector3 i_up)
{
  i_up = normalize(i_up);
  d_up = XMFLOAT3(i_up.x, i_up.y, i_up.z);
  updateViewMatrix();
}


Vector3 Camera::getLeft() const
{
  return normalize(cross(getForward(), getUp()));
}

Vector3 Camera::getRight() const
{
  return normalize(cross(getUp(), getForward()));
}

Vector3 Camera::getForward() const
{
  return Vector3{ d_direction.x, d_direction.y, d_direction.z };
}

Vector3 Camera::getBackward() const
{
  return Vector3{ -d_direction.x, -d_direction.y, -d_direction.z };
}


void Camera::updateProjectionMatrix(int i_screenWidth, int i_screenHeight)
{
  float screenAspect = (float)i_screenWidth / (float)i_screenHeight;
  d_projectionMatrix = XMMatrixPerspectiveFovLH(c_fovAngle, screenAspect, c_near, c_far);
}

void Camera::updateViewMatrix()
{
  XMFLOAT3 lookAt = {
    d_position.x + d_direction.x,
    d_position.y + d_direction.y,
    d_position.z + d_direction.z };

  d_viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&d_position), XMLoadFloat3(&lookAt), XMLoadFloat3(&d_up));
}
