#pragma once

#include "Circle.h"
#include "IRealObject.h"
#include "ModelFwd.h"

#include <Sdk/Vector.h>


class Object : public IRealObject
{
public:

  Object();

  ObjectId getId() const { return d_id; }

  virtual bool isCreature() const { return false; }

  ///
  /// IRealObject
  ///

  virtual bool isMovable() const override;
  virtual float getAcceleration() const override;
  virtual float getMaxSpeed() const override;
  virtual Vector3 getMovementDirection() const override;

  virtual Vector3 getPosition() const override;
  virtual void setPosition(Vector3 i_position) override;

  virtual Vector3 getSpeed() const override;
  virtual void setSpeed(Vector3 i_speed) override;

  virtual const IShape& getCollisionShape() const override;

  ///

  void setMovementDirection(Vector3 i_movementDirection);
  void resetMovementDirection();

  void setModelName(const std::string& i_modelName) { d_modelName = i_modelName; }
  const std::string& getModelName() const { return d_modelName; }

  void setRotation(const Vector3& i_rotation) { d_rotation = i_rotation; }
  const Vector3& getRotation() const { return d_rotation; }

  void setCurrentAction(std::shared_ptr<IAction> i_action);
  IActionPtr getCurrentAction();
  IActionPtr getCurrentAction() const;

  void setVisibility(bool i_visible) { d_visible = i_visible; }
  bool getVisibility() const { return d_visible; }

private:

  ObjectId d_id;
  static ObjectId s_nextId;

  std::string d_modelName;

  Vector3 d_movementDirection;
  Vector3 d_position;
  Vector3 d_speed;
  Vector3 d_rotation;

  Circle d_collisionShape;

  IActionPtr d_currentAction;

  bool d_visible;
};
