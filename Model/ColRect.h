#pragma once

#include "IColShape.h"

#include <Sdk/Rect.h>


class ColRect : public IColShape
{
public:
  ColRect(float i_width, float i_height) : d_rect(i_width, i_height) { }

  virtual ColShapeType getColShapeType() const override { return ColShapeType::Rect; }

  Rect& getRect() { return d_rect; }
  const Rect& getRect() const { return d_rect; }

private:
  Rect d_rect;
};
