#include "stdafx.h"
#include "PhysicsController.h"

#include "Collider.h"

#include <Model/Object.h>


namespace
{
  const float MinThreshold = 0.01f;
} // anonymous NS


void PhysicsController::updateObjects(ObjectPtrs& io_objects, double i_dt)
{
  for (auto objectPtr : io_objects)
  {
    if (!objectPtr->isMovable())
      continue;

    const auto virtualSpeed = getVirtualSpeed(objectPtr, i_dt);
    const auto realSpeed = getRealSpeed(objectPtr, i_dt, virtualSpeed, io_objects);
    applySpeed(objectPtr, i_dt, realSpeed);
  }
}


Vector3 PhysicsController::getVirtualSpeed(ObjectPtr io_object, double i_dt)
{
  const float acceleration = io_object->getAcceleration();
  const float maxSpeed = io_object->getMaxSpeed();

  const auto direction = io_object->getMovementDirection();
  auto speedVector = io_object->getSpeed();

  if (length(direction) >= MinThreshold)
  {
    // Have movement direction - accelerate this direction
    // Align speed with the direction vector
    speedVector = normalize(direction) * length(speedVector);
    speedVector += normalize(direction) * acceleration * (float)i_dt;
  }
  else if (length(speedVector) >= MinThreshold)
  {
    // No movement direction, but have some speed - reduce the speed
    speedVector -= normalize(speedVector) * acceleration * (float)i_dt;
  }

  const float speed = length(speedVector);
  if (speed < MinThreshold)
    return Vector3::zero();

  if (speed > maxSpeed)
  {
    const float speedDecreaseCoef = speed / maxSpeed;
    speedVector = speedVector / speedDecreaseCoef;
  }

  return speedVector;
}

Vector3 PhysicsController::getRealSpeed(ObjectPtr io_object, double i_dt,
                                        const Vector3& i_virtualSpeed, const ObjectPtrs& io_objects)
{
  auto realSpeed = i_virtualSpeed;

  for (auto objectPtr : io_objects)
  {
    if (objectPtr->getId() == io_object->getId())
      continue;

    Vector2 normal;
    if (!Collider::collide(io_object, objectPtr, normal))
      continue;

    float normalProjection = dot(xyz2xz(realSpeed), normal);
    if (normalProjection > 0)
    {
      // It is allowed to go FROM the collision
      continue;
    }

    auto normalSpeed = xy2x0z(normal * normalProjection);
    auto tangentSpeed = realSpeed - normalSpeed;

    if (length(tangentSpeed) >= MinThreshold)
      realSpeed = normalize(tangentSpeed) * length(i_virtualSpeed);
    else
      realSpeed = Vector3::zero();
  }

  return realSpeed;
}

void PhysicsController::applySpeed(ObjectPtr io_object, double i_dt, Vector3 i_speed)
{
  io_object->setSpeed(i_speed);

  auto newPosition = io_object->getPosition() + i_speed * (float)i_dt;
  newPosition.y = 1.0f; // place on terrain
  io_object->setPosition(newPosition);
}
