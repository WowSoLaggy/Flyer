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

  void setPosition(const Vector3& i_position) { d_position = i_position; }
  const Vector3& getPosition() const { return d_position; }

  void setRotation(const Vector3& i_rotation) { d_rotation = i_rotation; }
  const Vector3& getRotation() const { return d_rotation; }

  void setCurrentAction(std::shared_ptr<IAction> i_action);
  void resetCurrentAction();
  std::shared_ptr<IAction> getCurrentAction() const;

private:

  std::string d_modelName;
  std::string d_textureName;

  Vector3 d_position;
  Vector3 d_rotation;

  std::shared_ptr<IAction> d_currentAction;
};
