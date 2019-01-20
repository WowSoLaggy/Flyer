#pragma once

#include "Circle.h"
#include "Entity.h"
#include "ModelFwd.h"

#include <Sdk/Vector.h>


class Object : public Entity
{
public:

  Object();
  virtual ~Object() = default;

  virtual bool isMovable() const { return false; }
  float getAcceleration() const { return 10.0f; }
  float getMaxSpeed() const { return 2.0f; }

  Vector3 getSpeed() const { return d_speed; }
  void setSpeed(Vector3 i_speed) { d_speed = std::move(i_speed); }

  const IShape& getCollisionShape() const { return d_collisionShape; }

  Vector3 getMovementDirection() const { return d_movementDirection; }
  void setMovementDirection(Vector3 i_movementDirection) { d_movementDirection = std::move(i_movementDirection); }
  void resetMovementDirection() { d_movementDirection = Vector3::zero(); }

  void setCurrentAction(std::shared_ptr<IAction> i_action);
  IActionPtr getCurrentAction() const { return d_currentAction; }
  IActionPtr getCurrentAction() { return d_currentAction; }

private:

  Vector3 d_movementDirection;
  Vector3 d_speed;

  Circle d_collisionShape;

  IActionPtr d_currentAction;
};
