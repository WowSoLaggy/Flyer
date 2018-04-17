#pragma once


////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
  CameraClass();

  void SetPosition(float, float, float);
  void SetRotation(float, float, float);

  XMFLOAT3 GetPosition();
  XMFLOAT3 GetRotation();

  void Render();
  void GetViewMatrix(XMMATRIX&);

private:
  float d_positionX, d_positionY, d_positionZ;
  float d_rotationX, d_rotationY, d_rotationZ;
  XMMATRIX d_viewMatrix;
};
