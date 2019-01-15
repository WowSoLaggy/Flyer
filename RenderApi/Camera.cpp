#include "stdafx.h"
#include "Camera.h"


Camera::Camera(int i_screenWidth, int i_screenHeight)
  : d_position{ 1, 1, 1 }
  , d_lookAt{ 0, 0, 0 }
  , d_up{ 0, 1, 0 }
  , d_viewportWidth(i_screenWidth)
  , d_viewportHeight(i_screenHeight)
{
  updateProjectionMatrix();
}


Vector3 Camera::getPosition() const
{
  return { d_position.x, d_position.y, d_position.z };
}

Vector3 Camera::getLookAt() const
{
  return { d_lookAt.x, d_lookAt.y, d_lookAt.z };
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

void Camera::setLookAt(Vector3 i_lookAt)
{
  d_lookAt = XMFLOAT3(i_lookAt.x, i_lookAt.y, i_lookAt.z);
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
  return normalize(cross(getUp(), getForward()));
}

Vector3 Camera::getRight() const
{
  return -getLeft();
}

Vector3 Camera::getForward() const
{
  return Vector3{ d_position.x - d_lookAt.x, d_position.y - d_lookAt.y, d_position.z - d_lookAt.z };
}

Vector3 Camera::getBackward() const
{
  return -getForward();
}


void Camera::updateProjectionMatrix()
{
  float screenAspect = (float)d_viewportWidth/ (float)d_viewportHeight;
  d_projectionMatrix = XMMatrixPerspectiveFovRH(FovAngle, screenAspect,
                                                ViewportMinZ, ViewportMaxZ);
}

void Camera::updateViewMatrix()
{
  d_viewMatrix = XMMatrixLookAtRH(XMLoadFloat3(&d_position), XMLoadFloat3(&d_lookAt), XMLoadFloat3(&d_up));
}


Vector2 Camera::worldToScreen(const Vector3& i_point) const
{
  FXMVECTOR v1 = XMVectorSet(i_point.x, i_point.y, i_point.z, 1);
  auto worldMatrix = XMMatrixIdentity();

  auto res = XMVector3Project(v1, 0.0f, 0.0f,
                              (float)d_viewportWidth, (float)d_viewportHeight, ViewportMinZ, ViewportMaxZ,
                              d_projectionMatrix, d_viewMatrix, worldMatrix);

  XMFLOAT3 tempVector;
  XMStoreFloat3(&tempVector, res);
  return { tempVector.x, tempVector.y };
}
