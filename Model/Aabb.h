#pragma once

#include "IShape.h"


class Aabb : public IShape
{
public:
  Aabb(double i_width, double i_height)
    : d_width(i_width)
    , d_height(i_height)
  {
  }

  virtual ShapeType getShapeType() const override { return ShapeType::Aabb; }

  double getWidth() const { return d_width; }
  double getHeight() const { return d_height; }

private:
  double d_width;
  double d_height;
};
