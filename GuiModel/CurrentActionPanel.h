#pragma once

#include "IGui2d.h"

#include <Sdk/Vector.h>


class CurrentActionPanel : public IGui2d
{
public:

  CurrentActionPanel();

  void setPosition(Vector2 i_position) { d_position = std::move(i_position); }
  void setOffset(Vector2 i_offset) { d_offset = std::move(i_offset); }

  Vector2 getPosition() const;

  void setSize(Vector2 i_size) { d_size = std::move(i_size); }
  const Vector2& getSize() const { return d_size; }

  void setTextureName(std::string i_textureName) { d_textureName = std::move(i_textureName); }
  const std::string& getTextureName() const { return d_textureName; }

private:

  Vector2 d_position;
  Vector2 d_offset;

  Vector2 d_size;

  std::string d_textureName;
};
