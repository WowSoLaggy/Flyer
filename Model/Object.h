#pragma once

#include "ModelFwd.h"

#include <LaggySdk/IModelName.h>
#include <LaggySdk/IPosition3.h>
#include <LaggySdk/IRotation3.h>
#include <LaggySdk/IScale3.h>
#include <LaggySdk/ISpeed3.h>
#include <LaggySdk/IUniqueId.h>
#include <LaggySdk/IVisibility.h>
#include <LaggySdk/Vector.h>


class Object :
  public Sdk::IPosition3, public Sdk::IRotation3, public Sdk::ISpeed3, public Sdk::IScale3,
  public Sdk::IVisibility, public Sdk::IUniqueId,
  public Sdk::IModelName
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

  Sdk::Vector3 getMovementDirection() const { return d_movementDirection; }
  void setMovementDirection(Sdk::Vector3 i_movementDirection) { d_movementDirection = std::move(i_movementDirection); }
  void resetMovementDirection() { d_movementDirection = Sdk::Vector3::zero(); }

  void setCurrentAction(IActionPtr i_action);
  const IActionPtr& getCurrentAction() const { return d_currentAction; }
  IActionPtr getCurrentAction() { return d_currentAction; }

private:
  bool d_movable;
  float d_acceleration;
  float d_maxSpeed;
  Sdk::Vector3 d_movementDirection;

  IColShapePtr d_collisionShape;
  IActionPtr d_currentAction;
};
