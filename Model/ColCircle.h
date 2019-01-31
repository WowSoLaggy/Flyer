#pragma once

#include "IColShape.h"

#include <Sdk/Circle.h>


class ColCircle : public IColShape
{
public:
  ColCircle(float i_radius) : d_circle(i_radius) { }

  virtual ColShapeType getColShapeType() const override { return ColShapeType::Circle; }

  Circle& getCircle() { return d_circle; }
  const Circle& getCircle() const { return d_circle; }

private:
  Circle d_circle;
};
