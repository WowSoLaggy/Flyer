#include "stdafx.h"
#include "HealthBar.h"


HealthBar::HealthBar()
  : d_position({ 0, 0 })
  , d_frontOffset({ 0, 0 })
  , d_sizeBack({ 0, 0 })
  , d_sizeFront({ 0, 0 })
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
