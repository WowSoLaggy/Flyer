#pragma once

enum class ColShapeType
{
  Circle,
  Rect,
};

class IColShape
{
public:
  virtual ~IColShape() = default;

  virtual ColShapeType getColShapeType() const = 0;
};
