#include "stdafx.h"
#include "ObjectController.h"

#include <Model/ActionMoveTo.h>
#include <Model/Object.h>


void ObjectController::updateObject(Object& i_object, double i_dt)
{
  auto pAction = i_object.getCurrentAction();
  if (!pAction)
    return;

  if (const auto* pMoveToAction = dynamic_cast<ActionMoveTo*>(pAction.get()))
  {
    auto position = i_object.getPosition();
    auto goal = pMoveToAction->getGoal();

    if (lengthSq(goal - position) <= pMoveToAction->getToleranceSq())
    {
      float newX = (float)(std::rand() % 180 - 90) / 10;
      float newY = (float)(std::rand() % 180 - 90) / 10;
      i_object.setCurrentAction(std::make_shared<ActionMoveTo>(ActionMoveTo({ newX, newY })));
      return;
    }

    const float speed = 0.1f;
    auto movement = normalize(goal - position) * speed;

    i_object.setPosition(i_object.getPosition() + movement);
  }
}
