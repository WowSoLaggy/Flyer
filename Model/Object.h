#pragma once

#include "Circle.h"
#include "ModelFwd.h"

#include <Sdk/IModelName.h>
#include <Sdk/IPosition3.h>
#include <Sdk/IRotation3.h>
#include <Sdk/ISpeed3.h>
#include <Sdk/IUniqueId.h>
#include <Sdk/IVisibility.h>
#include <Sdk/Vector.h>


class Object :
  public IPosition3, public IRotation3, public ISpeed3,
  public IVisibility, public IUniqueId,
  public IModelName
{
public:

  Object();
  virtual ~Object() = default;

  virtual bool isCreature() const { return false; }
  virtual bool isMovable() const { return false; }
  virtual float getAcceleration() const { return 0.0f; }
  virtual float getMaxSpeed() const { return 0.0f; }

  bool hasCollisionShape() const { return d_collisionShape != nullptr; }
  const IShapePtr& getCollisionShape() const { return d_collisionShape; }
  IShapePtr getCollisionShape() { return d_collisionShape; }

  Vector3 getMovementDirection() const { return d_movementDirection; }
  void setMovementDirection(Vector3 i_movementDirection) { d_movementDirection = std::move(i_movementDirection); }
  void resetMovementDirection() { d_movementDirection = Vector3::zero(); }

  void setCurrentAction(std::shared_ptr<IAction> i_action);
  const IActionPtr& getCurrentAction() const { return d_currentAction; }
  IActionPtr getCurrentAction() { return d_currentAction; }

private:
  Vector3 d_movementDirection;

  IShapePtr d_collisionShape;
  IActionPtr d_currentAction;
};
