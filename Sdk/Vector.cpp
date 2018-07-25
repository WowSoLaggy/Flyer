#include "stdafx.h"
#include "Vector.h"


Vector3 operator+(const Vector3& i_left, const Vector3& i_right)
{
  return { i_left.x + i_right.x, i_left.y + i_right.y, i_left.z + i_right.z };
}

Vector3 operator-(const Vector3& i_left, const Vector3& i_right)
{
  return { i_left.x - i_right.x, i_left.y - i_right.y, i_left.z - i_right.z };
}
