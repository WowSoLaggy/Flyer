#pragma once


struct MatrixBuffer
{
  XMMATRIX world;
  XMMATRIX view;
  XMMATRIX projection;
};


struct LightBuffer
{
  XMFLOAT4 diffuseColor;
  XMFLOAT3 lightDirection;
  float padding;  // Extra padding so structure is a multiple of 16 for CreateBuffer function requirements
};
