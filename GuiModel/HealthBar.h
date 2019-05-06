#pragma once

#include "IGui2d.h"

#include <LaggySdk/Vector.h>


class HealthBar : public IGui2d
{
public:

  HealthBar();

  void setPosition(Sdk::Vector2 i_position) { d_position = std::move(i_position); }
  void setOffset(Sdk::Vector2 i_offset) { d_offset = std::move(i_offset); }
  void setFrontOffset(Sdk::Vector2 i_frontOffset) { d_frontOffset = std::move(i_frontOffset); }

  Sdk::Vector2 getPositionBack() const;
  Sdk::Vector2 getPositionFront() const;

  void setSizeBack(Sdk::Vector2 i_sizeBack) { d_sizeBack = std::move(i_sizeBack); }
  const Sdk::Vector2& getSizeBack() const { return d_sizeBack; }

  void setSizeFront(Sdk::Vector2 i_sizeFront) { d_sizeFront = std::move(i_sizeFront); }
  Sdk::Vector2 getSizeFront() const;

  void setValue(double i_value) { d_value = i_value; }

  void setTextureBackName(std::string i_textureBackName) { d_textureBackName = std::move(i_textureBackName); }
  const std::string& getTextureBackName() const { return d_textureBackName; }

  void setTextureFrontName(std::string i_textureFrontName) { d_textureFrontName = std::move(i_textureFrontName); }
  const std::string& getTextureFrontName() const { return d_textureFrontName; }

private:

  Sdk::Vector2 d_position;
  Sdk::Vector2 d_offset;
  Sdk::Vector2 d_frontOffset;

  Sdk::Vector2 d_sizeBack;
  Sdk::Vector2 d_sizeFront;

  double d_value;

  std::string d_textureBackName;
  std::string d_textureFrontName;
};
