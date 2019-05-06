#pragma once

#include "IColShape.h"

#include <LaggySdk/Circle.h>


class ColCircle : public IColShape
{
public:
  ColCircle(float i_radius) : d_circle(i_radius) { }

  virtual ColShapeType getColShapeType() const override { return ColShapeType::Circle; }

  Sdk::Circle& getCircle() { return d_circle; }
  const Sdk::Circle& getCircle() const { return d_circle; }

private:
  Sdk::Circle d_circle;
};
