#include "stdafx.h"
#include "PhysicsController.h"

#include <Model/IRealObject.h>


namespace
{
  const float MinThreshold = 0.01f;
} // anonymous NS


void PhysicsController::updateObjects(std::vector<IRealObjectPtr>& io_objects, double i_dt)
{
  for (auto realObjectPtr : io_objects)
  {
    if (!realObjectPtr->isMovable())
      continue;

    const auto virtualSpeed = getVirtualSpeed(realObjectPtr, i_dt);
    applySpeed(realObjectPtr, i_dt, realSpeed);
  }
}


Vector3 PhysicsController::getVirtualSpeed(IRealObjectPtr io_object, double i_dt)
{
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
  if (speed < MinThreshold)
    return Vector3::zero();

  if (speed > maxSpeed)
  {
    const float speedDecreaseCoef = speed / maxSpeed;
    speedVector = speedVector / speedDecreaseCoef;
  }

  return speedVector;
}

void PhysicsController::applySpeed(IRealObjectPtr io_object, double i_dt, Vector3 i_speed)
{
  io_object->setSpeed(i_speed);

  auto newPosition = io_object->getPosition() + i_speed * (float)i_dt;
  newPosition.y = 1.0f; // place on terrain
  io_object->setPosition(newPosition);
}
