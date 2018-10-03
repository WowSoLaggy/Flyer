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
    auto goal = pMoveToAction->getGoal();

    if (lengthSq(goal - position) <= pMoveToAction->getToleranceSq())
    {
      double timeToHold = (double)(std::rand() % 50) / 10;
      io_object.setCurrentAction(std::make_shared<ActionHold>(ActionHold(timeToHold)));
      return;
    }

    const float speed = 0.1f;
    auto movement = normalize(goal - position) * speed;

    io_object.setPosition(io_object.getPosition() + movement);
  }
  else if (auto* pHoldAction = dynamic_cast<ActionHold*>(pAction.get()))
  {
    if (!pHoldAction->hold(i_dt))
    {
      float newX = (float)(std::rand() % 180 - 90) / 10;
      float newY = (float)(std::rand() % 180 - 90) / 10;
      io_object.setCurrentAction(std::make_shared<ActionMoveTo>(ActionMoveTo({ newX, newY })));
    }
  }
}
