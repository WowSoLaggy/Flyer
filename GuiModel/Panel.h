#pragma once

#include "IGui2d.h"

#include <Sdk/Vector.h>


class Panel : public IGui2d
{
public:

  Panel();

  void setPosition(Vector2 i_position) { d_position = std::move(i_position); }
  const Vector2& getPosition() const { return d_position; }

  void setTextureName(std::string i_textureName) { d_textureName = std::move(i_textureName); }
  const std::string& getTextureName() const { return d_textureName; }

private:

  Vector2 d_position;
  std::string d_textureName;
};
