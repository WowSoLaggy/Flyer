#pragma once

#include <Sdk/Vector.h>

class Object
{
public:

  void setModelName(const std::string& i_modelName) { d_modelName = i_modelName; }
  const std::string& getModelName() const { return d_modelName; }

  void setTextureName(const std::string& i_textureName) { d_textureName = i_textureName; }
  const std::string& getTextureName() const { return d_textureName; }

  void setPosition(const Vector2& i_position) { d_position = i_position; }
  const Vector2& getPosition() const { return d_position; }

private:

  std::string d_modelName;
  std::string d_textureName;

  Vector2 d_position;

};
