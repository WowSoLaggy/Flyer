#include "stdafx.h"
#include "HealthBar.h"


HealthBar::HealthBar()
  : d_position({ 0, 0 })
  , d_frontOffset({ 0, 0 })
  , d_sizeBack({ 0, 0 })
  , d_sizeFront({ 0, 0 })
  , d_textureBackName("")
  , d_textureFrontName("")
{
}
