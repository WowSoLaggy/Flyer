#include "stdafx.h"
#include "CurrentActionPanel.h"


CurrentActionPanel::CurrentActionPanel()
  : d_position(Vector2::zero())
  , d_offset(Vector2::zero())
  , d_size(Vector2::zero())
  , d_textureName("")
{
}


Vector2 CurrentActionPanel::getPosition() const
{
  return d_position + d_offset;
}
