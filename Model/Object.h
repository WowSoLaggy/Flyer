#pragma once

#include "ModelFwd.h"

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

  void setCurrentAction(std::shared_ptr<IAction> i_action);
  void resetCurrentAction();
  std::shared_ptr<IAction> getCurrentAction() const;

private:

  std::string d_modelName;
  std::string d_textureName;

  Vector2 d_position;

  std::shared_ptr<IAction> d_currentAction;
};
