#include "stdafx.h"
#include "CurrentActionPanel.h"


CurrentActionPanel::CurrentActionPanel()
  : d_position(Sdk::Vector2::zero())
  , d_offset(Sdk::Vector2::zero())
  , d_size(Sdk::Vector2::zero())
  , d_textureName("")
{
}


Sdk::Vector2 CurrentActionPanel::getPosition() const
{
  return d_position + d_offset;
}
