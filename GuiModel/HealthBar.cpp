#include "stdafx.h"
#include "HealthBar.h"


HealthBar::HealthBar()
  : d_position(Vector2::zero())
  , d_offset(Vector2::zero())
  , d_frontOffset(Vector2::zero())
  , d_sizeBack(Vector2::zero())
  , d_sizeFront(Vector2::zero())
  , d_value(1)
  , d_textureBackName("")
  , d_textureFrontName("")
{
}


Vector2 HealthBar::getPositionBack() const
{
  return d_position + d_offset;
}

Vector2 HealthBar::getPositionFront() const {
  return d_position + d_offset + d_frontOffset;
}


Vector2 HealthBar::getSizeFront() const
{
  return { (float)(d_sizeFront.x * d_value), d_sizeFront.y };
}
