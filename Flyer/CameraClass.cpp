#include "stdafx.h"
#include "CameraClass.h"


CameraClass::CameraClass()
{
  d_positionX = 0.0f;
  d_positionY = 0.0f;
  d_positionZ = 0.0f;

  d_rotationX = 0.0f;
  d_rotationY = 0.0f;
  d_rotationZ = 0.0f;
}


void CameraClass::SetPosition(float x, float y, float z)
{
  d_positionX = x;
  d_positionY = y;
  d_positionZ = z;
}

void CameraClass::SetRotation(float x, float y, float z)
{
  d_rotationX = x;
  d_rotationY = y;
  d_rotationZ = z;
}


XMFLOAT3 CameraClass::GetPosition()
{
  return XMFLOAT3(d_positionX, d_positionY, d_positionZ);
}

XMFLOAT3 CameraClass::GetRotation()
{
  return XMFLOAT3(d_rotationX, d_rotationY, d_rotationZ);
}


void CameraClass::Render()
{
  XMFLOAT3 up, position, lookAt;
  float yaw, pitch, roll;
  XMMATRIX rotationMatrix;


  // Setup the vector that points upwards.
  up.x = 0.0f;
  up.y = 1.0f;
  up.z = 0.0f;

  // Setup the position of the camera in the world.
  position.x = d_positionX;
  position.y = d_positionY;
  position.z = d_positionZ;

  // Setup where the camera is looking by default.
  lookAt.x = 0.0f;
  lookAt.y = 0.0f;
  lookAt.z = 1.0f;

  // Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
  pitch = d_rotationX * 0.0174532925f;
  yaw = d_rotationY * 0.0174532925f;
  roll = d_rotationZ * 0.0174532925f;

  // Create the rotation matrix from the yaw, pitch, and roll values.
  rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

  // Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
  XMStoreFloat3(&lookAt, XMVector3TransformCoord(XMLoadFloat3(&lookAt), rotationMatrix));
  XMStoreFloat3(&up, XMVector3TransformCoord(XMLoadFloat3(&up), rotationMatrix));

  // Translate the rotated camera position to the location of the viewer.
  lookAt = XMFLOAT3(position.x + lookAt.x, position.y + lookAt.y, position.z + lookAt.z);

  // Finally create the view matrix from the three updated vectors.
  d_viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&position), XMLoadFloat3(&lookAt), XMLoadFloat3(&up));
}

void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
  viewMatrix = d_viewMatrix;
}
