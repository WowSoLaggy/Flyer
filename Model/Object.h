#pragma once

#include "Circle.h"
#include "ModelFwd.h"

#include <Sdk/IPosition3.h>
#include <Sdk/IRotation3.h>
#include <Sdk/ISpeed3.h>
#include <Sdk/IUniqueId.h>
#include <Sdk/IVisibility.h>
#include <Sdk/Vector.h>


class Object :
  public IPosition3, public IRotation3, public IVisibility, public IUniqueId, public ISpeed3
{
public:

  Object();
  virtual ~Object() = default;

  virtual bool isCreature() const { return false; }
  virtual bool isMovable() const { return false; }
  virtual float getAcceleration() const { return 0.0f; }
  virtual float getMaxSpeed() const { return 0.0f; }

  const std::string& getModelName() const { return d_modelName; }
  void setModelName(const std::string& i_modelName) { d_modelName = i_modelName; }

  const std::string& getCustomTextureName() const { return d_customTextureName; }
  void setCustomTextureName(const std::string& i_customTextureName) { d_customTextureName = i_customTextureName; }

  const IShape& getCollisionShape() const { return d_collisionShape; }

  Vector3 getMovementDirection() const { return d_movementDirection; }
  void setMovementDirection(Vector3 i_movementDirection) { d_movementDirection = std::move(i_movementDirection); }
  void resetMovementDirection() { d_movementDirection = Vector3::zero(); }

  void setCurrentAction(std::shared_ptr<IAction> i_action);
  IActionPtr getCurrentAction() const { return d_currentAction; }
  IActionPtr getCurrentAction() { return d_currentAction; }

private:

  std::string d_modelName;
  std::string d_customTextureName;

  Vector3 d_movementDirection;

  Circle d_collisionShape;
  IActionPtr d_currentAction;
};
