#pragma once

#include "ModelFwd.h"

#include <Sdk/Vector.h>


class IRealObject
{
public:
  virtual ~IRealObject() = default;


  virtual bool isMovable() const = 0;
  virtual float getAcceleration() const = 0;
  virtual float getMaxSpeed() const = 0;
  virtual Vector3 getMovementDirection() const = 0;

  virtual Vector3 getPosition() const = 0;
  virtual void setPosition(Vector3 i_position) = 0;

  virtual Vector3 getSpeed() const = 0;
  virtual void setSpeed(Vector3 i_speed) = 0;

  virtual const IShape& getCollisionShape() const = 0;
};
