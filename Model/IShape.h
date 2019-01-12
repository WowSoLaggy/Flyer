#pragma once

enum class ShapeType
{
  Circle,
};

class IShape
{
public:
  virtual ~IShape() = default;

  virtual ShapeType getShapeType() const = 0;
};
