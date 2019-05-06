#include "stdafx.h"
#include "HealthBar.h"


HealthBar::HealthBar()
  : d_position(Sdk::Vector2::zero())
  , d_offset(Sdk::Vector2::zero())
  , d_frontOffset(Sdk::Vector2::zero())
  , d_sizeBack(Sdk::Vector2::zero())
  , d_sizeFront(Sdk::Vector2::zero())
  , d_value(1)
  , d_textureBackName("")
  , d_textureFrontName("")
{
}


Sdk::Vector2 HealthBar::getPositionBack() const
{
  return d_position + d_offset;
}

Sdk::Vector2 HealthBar::getPositionFront() const {
  return d_position + d_offset + d_frontOffset;
}


Sdk::Vector2 HealthBar::getSizeFront() const
{
  return { (float)(d_sizeFront.x * d_value), d_sizeFront.y };
}
