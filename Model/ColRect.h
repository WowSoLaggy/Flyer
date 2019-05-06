#pragma once

#include "IColShape.h"

#include <LaggySdk/Rect.h>


class ColRect : public IColShape
{
public:
  ColRect(float i_width, float i_height) : d_rect(i_width, i_height) { }

  virtual ColShapeType getColShapeType() const override { return ColShapeType::Rect; }

  Sdk::Rect& getRect() { return d_rect; }
  const Sdk::Rect& getRect() const { return d_rect; }

private:
  Sdk::Rect d_rect;
};
