#include "stdafx.h"
#include "CreatureController.h"

#include "WorldController.h"

#include <Model/ActionMoveTo.h>
#include <Model/Creature.h>
#include <Model/Object.h>
#include <Model/World.h>


namespace
{

  {


  }

} // anonymous NS


void CreatureController::updateObject(CreaturePtr io_creature, double i_dt,
                                    WorldController& io_worldController)
{
  auto& action = io_creature->getCurrentAction();
  switch (action.getActionType())
  {
  {
    break;

  case ActionType::MoveTo:
  {
    const auto& moveToAction = dynamic_cast<const ActionMoveTo&>(action);
    auto position = io_creature->getPosition();
    Vector2 position2 = { position.x, position.z };
    auto goal = moveToAction.getGoal();

    auto direction = goal - position2;

    if (lengthSq(direction) <= moveToAction.getToleranceSq())
    {
      double timeToHold = (double)(std::rand() % 50) / 10;
      io_creature->setCurrentAction(std::make_shared<ActionIdle>());
      return;
    }

    const float maxSpeed = 1.0f;
    auto movement = normalize(direction) * maxSpeed * (float)i_dt;

    io_creature->setPosition(io_creature->getPosition() + Vector3{ movement.x, 0, movement.y });
    io_creature->setRotation({ 0, -std::atan2(direction.y, direction.x), 0 });

    break;
  }

  } // switch (action.getActionType())
}
