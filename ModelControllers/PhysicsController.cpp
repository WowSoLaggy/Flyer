#include "stdafx.h"
#include "PhysicsController.h"

#include <Model/IRealObject.h>


void PhysicsController::updateObjects(std::vector<IRealObjectPtr>& io_objects, double i_dt)
{
  for (auto realObjectPtr : io_objects)
    updateObject(realObjectPtr, i_dt);
}


void PhysicsController::updateObject(IRealObjectPtr io_object, double i_dt)
{
  if (!io_object->isMovable())
    return;

  const float MinThreshold = 0.01f;
  const float acceleration = io_object->getAcceleration();
  const float maxSpeed = io_object->getMaxSpeed();

  const auto direction = io_object->getMovementDirection();
  auto speedVector = io_object->getSpeed();

  auto accelerationVector = Vector3::zero();
  if (length(direction) >= MinThreshold)
  {
    // Have movement direction - accelerate this direction
    accelerationVector = normalize(direction) * acceleration;
  }
  else if (length(speedVector) >= MinThreshold)
  {
    // No movement direction, but have some speed - reduce the speed
    accelerationVector = normalize(speedVector) * -acceleration;
  }

  if (length(accelerationVector) >= MinThreshold)
    speedVector += accelerationVector * (float)i_dt;

  const float speed = length(speedVector);
  if (speed > maxSpeed)
  {
    const float speedDecreaseCoef = speed / maxSpeed;
    speedVector = speedVector / speedDecreaseCoef;
  }
  if (speed < MinThreshold)
    speedVector = Vector3::zero();
  io_object->setSpeed(speedVector);

  auto newPosition = io_object->getPosition() + speedVector * (float)i_dt;
  newPosition.y = 1.0f; // place on terrain
  io_object->setPosition(newPosition);
}
