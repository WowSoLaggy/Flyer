#pragma once

#include "ModelFwd.h"

#include <Sdk/Vector.h>


class Object
{
public:

  Object();

  ObjectId getId() const { return d_id; }

  virtual bool isCreature() const { return false; }

  void setModelName(const std::string& i_modelName) { d_modelName = i_modelName; }
  const std::string& getModelName() const { return d_modelName; }

  void setPosition(const Vector3& i_position) { d_position = i_position; }
  const Vector3& getPosition() const { return d_position; }

  void setRotation(const Vector3& i_rotation) { d_rotation = i_rotation; }
  const Vector3& getRotation() const { return d_rotation; }

  void setCurrentAction(std::shared_ptr<IAction> i_action);
  IAction& getCurrentAction();
  const IAction& getCurrentAction() const;

  void setVisibility(bool i_visible) { d_visible = i_visible; }
  bool getVisibility() const { return d_visible; }

private:

  ObjectId d_id;
  static ObjectId s_nextId;

  std::string d_modelName;

  Vector3 d_position;
  Vector3 d_rotation;

  std::shared_ptr<IAction> d_currentAction;

  bool d_visible;
};
