#pragma once

#include "IGui.h"

#include <Sdk/Vector.h>


class HealthBar : public IGui
{
public:

  HealthBar();

  void setPosition(Vector2 i_position) { d_position = std::move(i_position); }
  void setOffset(Vector2 i_offset) { d_frontOffset = std::move(i_offset); }

  const Vector2& getPositionBack() const { return d_position; }
  Vector2 getPositionFront() const { return d_position + d_frontOffset; }

  void setTextureBackName(std::string i_textureBackName) { d_textureBackName = std::move(i_textureBackName); }
  const std::string& getTextureBackName() const { return d_textureBackName; }

  void setTextureFrontName(std::string i_textureFrontName) { d_textureFrontName = std::move(i_textureFrontName); }
  const std::string& getTextureFrontName() const { return d_textureFrontName; }

private:

  Vector2 d_position;
  Vector2 d_frontOffset;

  std::string d_textureBackName;
  std::string d_textureFrontName;
};
