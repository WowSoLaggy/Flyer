#include "stdafx.h"
#include "ObjectController.h"

#include <Model/ActionHold.h>
#include <Model/ActionMoveTo.h>
#include <Model/Object.h>


void ObjectController::updateObject(Object& io_object, double i_dt)
{
  auto pAction = io_object.getCurrentAction();
  if (!pAction)
    return;

  if (const auto* pMoveToAction = dynamic_cast<ActionMoveTo*>(pAction.get()))
  {
    auto position = io_object.getPosition();
    Vector2 position2 = { position.x, position.z };
    auto goal = pMoveToAction->getGoal();

    if (lengthSq(goal - position2) <= pMoveToAction->getToleranceSq())
    {
      double timeToHold = (double)(std::rand() % 50) / 10;
      io_object.setCurrentAction(std::make_shared<ActionHold>(ActionHold(timeToHold)));
      return;
    }

    const float maxSpeed = 1.0f;
    auto movement = normalize(goal - position2) * maxSpeed * (float)i_dt;

    io_object.setPosition(io_object.getPosition() + Vector3{ movement.x, 0, movement.y });
  }
  else if (auto* pHoldAction = dynamic_cast<ActionHold*>(pAction.get()))
  {
    if (!pHoldAction->hold(i_dt))
    {
      float newX = (float)(std::rand() % 100 + 20) / 10;
      float newY = (float)(std::rand() % 160 + 20) / 10;
      io_object.setCurrentAction(std::make_shared<ActionMoveTo>(ActionMoveTo({ newX, newY })));
    }
  }
}
