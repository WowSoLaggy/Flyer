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

Vector3 operator*(const Vector3& i_v, float i_mul);

float length(const Vector3& i_v);
float lengthSq(const Vector3& i_v);
Vector3 normalize(const Vector3& i_v);

Vector3 cross(const Vector3& i_left, const Vector3& i_right);
