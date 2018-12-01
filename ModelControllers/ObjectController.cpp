#include "stdafx.h"
#include "ObjectController.h"

#include <Model/ActionHold.h>
#include <Model/ActionMoveTo.h>
#include <Model/Object.h>


void ObjectController::updateObject(Object& io_object, double i_dt)
{
  auto& action = io_object.getCurrentAction();
  switch (action.getActionType())
  {
  case ActionType::Hold:
  {
    auto& holdAction = dynamic_cast<ActionHold&>(action);
    if (!holdAction.hold(i_dt))
    {
      float newX = (float)(std::rand() % 100 + 20) / 10;
      float newY = (float)(std::rand() % 160 + 20) / 10;
      io_object.setCurrentAction(std::make_shared<ActionMoveTo>(ActionMoveTo({ newX, newY })));
    }
    break;
  }
  case ActionType::MoveTo:
  {
    const auto& moveToAction = dynamic_cast<const ActionMoveTo&>(action);
    auto position = io_object.getPosition();
    Vector2 position2 = { position.x, position.z };
    auto goal = moveToAction.getGoal();

    auto direction = goal - position2;

    if (lengthSq(direction) <= moveToAction.getToleranceSq())
    {
      double timeToHold = (double)(std::rand() % 50) / 10;
      io_object.setCurrentAction(std::make_shared<ActionHold>(ActionHold(timeToHold)));
      return;
    }

    const float maxSpeed = 1.0f;
    auto movement = normalize(direction) * maxSpeed * (float)i_dt;

    io_object.setPosition(io_object.getPosition() + Vector3{ movement.x, 0, movement.y });
    io_object.setRotation({ 0, -std::atan2(direction.y, direction.x), 0 });

    break;
  }

  } // switch
}
