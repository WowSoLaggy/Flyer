#pragma once

#include "ModelFwd.h"

#include <Sdk/IModelName.h>
#include <Sdk/IPosition3.h>
#include <Sdk/IRotation3.h>
#include <Sdk/IScale3.h>
#include <Sdk/ISpeed3.h>
#include <Sdk/IUniqueId.h>
#include <Sdk/IVisibility.h>
#include <Sdk/Vector.h>


class Object :
  public IPosition3, public IRotation3, public ISpeed3, public IScale3,
  public IVisibility, public IUniqueId,
  public IModelName
{
public:

  Object();
  virtual ~Object() = default;

  virtual bool isCreature() const { return false; }

  bool isMovable() const { return d_movable; }
  void setMovable(bool i_movable) { d_movable = i_movable; }

  float getAcceleration() const { return d_acceleration; }
  void setAcceleration(float i_acceleration) { d_acceleration = i_acceleration; }

  float getMaxSpeed() const { return d_maxSpeed; }
  void setMaxSpeed(float i_maxSpeed) { d_maxSpeed = i_maxSpeed; }

  bool hasCollisionShape() const { return d_collisionShape != nullptr; }
  const IColShapePtr& getCollisionShape() const { return d_collisionShape; }
  IColShapePtr getCollisionShape() { return d_collisionShape; }
  void setCollisionShape(IColShapePtr i_collisionShape) { d_collisionShape = i_collisionShape; }

  Vector3 getMovementDirection() const { return d_movementDirection; }
  void setMovementDirection(Vector3 i_movementDirection) { d_movementDirection = std::move(i_movementDirection); }
  void resetMovementDirection() { d_movementDirection = Vector3::zero(); }

  void setCurrentAction(IActionPtr i_action);
  const IActionPtr& getCurrentAction() const { return d_currentAction; }
  IActionPtr getCurrentAction() { return d_currentAction; }

private:
  bool d_movable;
  float d_acceleration;
  float d_maxSpeed;
  Vector3 d_movementDirection;

  IColShapePtr d_collisionShape;
  IActionPtr d_currentAction;
};
