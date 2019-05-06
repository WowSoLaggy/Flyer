#pragma once

#include "IGui2d.h"

#include <LaggySdk/Vector.h>


class CurrentActionPanel : public IGui2d
{
public:

  CurrentActionPanel();

  void setPosition(Sdk::Vector2 i_position) { d_position = std::move(i_position); }
  void setOffset(Sdk::Vector2 i_offset) { d_offset = std::move(i_offset); }

  Sdk::Vector2 getPosition() const;

  void setSize(Sdk::Vector2 i_size) { d_size = std::move(i_size); }
  const Sdk::Vector2& getSize() const { return d_size; }

  void setTextureName(std::string i_textureName) { d_textureName = std::move(i_textureName); }
  const std::string& getTextureName() const { return d_textureName; }

private:

  Sdk::Vector2 d_position;
  Sdk::Vector2 d_offset;

  Sdk::Vector2 d_size;

  std::string d_textureName;
};
