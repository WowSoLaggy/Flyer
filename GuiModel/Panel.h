#pragma once

#include "IGui.h"

#include <Sdk/Vector.h>


class Panel : public IGui
{
public:

  Panel();

  void setPosition(Vector2 i_position) { d_position = std::move(i_position); }
  const Vector2& getPosition() const { return d_position; }
  const std::string& getTextureName() const { return d_textureName; }

private:

  const std::string d_textureName;
  Vector2 d_position;
};
