#pragma once

#include "IShape.h"


class Circle : public IShape
{
public:

  virtual ShapeType getShapeType() const override { return ShapeType::Circle; }

  void setRadius(double i_radius) { d_radius = i_radius; d_radiusSq = i_radius * i_radius; }
  double getRadius() const { return d_radius; }
  double getRadiusSq() const { return d_radiusSq; }

private:
  double d_radius;
  double d_radiusSq;
};
