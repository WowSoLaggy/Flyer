#pragma once

#include "Vector.h"


class Rect
{
public:
  Rect(float i_width, float i_height);

  float getWidth() const { return d_width; }
  float getHeight() const { return d_height; }

  void setWidth(float i_width);
  void setHeight(float i_height);

  bool containsPoint(const Vector2& i_point) const;

private:
  float d_width;
  float d_height;
  float d_widthHalf;
  float d_heightHalf;
};
