#pragma once

#include "IShape.h"


class Circle : public IShape
{
public:

  Circle();
  Circle(double i_radius);

  virtual ShapeType getShapeType() const override { return ShapeType::Circle; }

  double getRadius() const { return d_radius; }
  double getRadiusSq() const { return d_radiusSq; }

  void setRadius(double i_radius);

private:
  double d_radius;
  double d_radiusSq;
};
