#pragma once

#include "IGui.h"

#include <Sdk/Vector.h>


class HealthBar : public IGui
{
public:

  HealthBar();

  void setPosition(Vector2 i_position) { d_position = std::move(i_position); }
  void setOffset(Vector2 i_offset) { d_offset = std::move(i_offset); }
  void setFrontOffset(Vector2 i_frontOffset) { d_frontOffset = std::move(i_frontOffset); }

  Vector2 getPositionBack() const { return d_position + d_offset; }
  Vector2 getPositionFront() const { return d_position + d_offset + d_frontOffset; }

  void setSizeBack(Vector2 i_sizeBack) { d_sizeBack = std::move(i_sizeBack); }
  const Vector2& getSizeBack() const { return d_sizeBack; }

  void setSizeFront(Vector2 i_sizeFront) { d_sizeFront = std::move(i_sizeFront); }
  const Vector2& getSizeFront() const { return d_sizeFront; }

  void setTextureBackName(std::string i_textureBackName) { d_textureBackName = std::move(i_textureBackName); }
  const std::string& getTextureBackName() const { return d_textureBackName; }

  void setTextureFrontName(std::string i_textureFrontName) { d_textureFrontName = std::move(i_textureFrontName); }
  const std::string& getTextureFrontName() const { return d_textureFrontName; }

private:

  Vector2 d_position;
  Vector2 d_offset;
  Vector2 d_frontOffset;

  Vector2 d_sizeBack;
  Vector2 d_sizeFront;

  std::string d_textureBackName;
  std::string d_textureFrontName;
};
