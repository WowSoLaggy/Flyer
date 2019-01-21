#pragma once

#include "Vector.h"


class IRotation3
{
public:
  IRotation3() : d_rotation(Vector3::zero()) { }
  virtual ~IRotation3() = default;

  Vector3 getRotation() const { return d_rotation; }
  void setRotation(Vector3 i_rotation) { d_rotation = std::move(i_rotation); }

private:
  Vector3 d_rotation;
};
