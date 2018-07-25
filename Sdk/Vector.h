#pragma once

struct Vector2
{
  float x;
  float y;
};

struct Vector3
{
  float x;
  float y;
  float z;
};

Vector3 operator+(const Vector3& i_left, const Vector3& i_right);
Vector3 operator-(const Vector3& i_left, const Vector3& i_right);
