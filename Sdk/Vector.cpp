#include "stdafx.h"
#include "Vector.h"


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Vector2
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


Vector2 operator+(const Vector2& i_left, const Vector2& i_right)
{
  return { i_left.x + i_right.x, i_left.y + i_right.y };
}

Vector2 operator-(const Vector2& i_left, const Vector2& i_right)
{
  return { i_left.x - i_right.x, i_left.y - i_right.y };
}


Vector2 operator*(const Vector2& i_v, float i_mul)
{
  return { i_v.x * i_mul, i_v.y * i_mul };
}


float length(const Vector2& i_v)
{
  return std::sqrtf(lengthSq(i_v));
}

float lengthSq(const Vector2& i_v)
{
  return i_v.x * i_v.x + i_v.y * i_v.y;
}

Vector2 normalize(const Vector2& i_v)
{
  float d = length(i_v);
  return { i_v.x / d, i_v.y / d };
}


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Vector3
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


Vector3 operator+(const Vector3& i_left, const Vector3& i_right)
{
  return { i_left.x + i_right.x, i_left.y + i_right.y, i_left.z + i_right.z };
}

Vector3 operator-(const Vector3& i_left, const Vector3& i_right)
{
  return { i_left.x - i_right.x, i_left.y - i_right.y, i_left.z - i_right.z };
}


Vector3 operator+=(Vector3& i_left, const Vector3& i_right)
{
  i_left.x += i_right.x;
  i_left.y += i_right.y;
  i_left.z += i_right.z;
  return i_left;
}

Vector3 operator-=(Vector3& i_left, const Vector3& i_right)
{
  i_left.x -= i_right.x;
  i_left.y -= i_right.y;
  i_left.z -= i_right.z;
  return i_left;
}


Vector3 operator-(const Vector3& i_v)
{
  return { -i_v.x, -i_v.y, -i_v.z };
}


Vector3 operator*(const Vector3& i_v, float i_mul)
{
  return { i_v.x * i_mul, i_v.y * i_mul, i_v.z * i_mul };
}

Vector3 operator/(const Vector3& i_v, float i_mul)
{
  return i_v * (1 / i_mul);
}


float length(const Vector3& i_v)
{
  return std::sqrtf(lengthSq(i_v));
}

float lengthSq(const Vector3& i_v)
{
  return i_v.x * i_v.x + i_v.y * i_v.y + i_v.z * i_v.z;
}

Vector3 normalize(const Vector3& i_v)
{
  float d = length(i_v);
  return { i_v.x / d, i_v.y / d, i_v.z / d };
}


Vector3 cross(const Vector3& i_left, const Vector3& i_right)
{
  return {
    i_left.y * i_right.z - i_left.z * i_right.y,
    i_left.z * i_right.x - i_left.x * i_right.z,
    i_left.x * i_right.y - i_left.y * i_right.x };
}


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Common
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


Vector2 xyz2xz(const Vector3& i_v)
{
  return Vector2{ i_v.x, i_v.z };
}
