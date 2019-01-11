#include "stdafx.h"
#include "CreatureController.h"

#include "WorldController.h"

#include <Model/ActionAttack.h>
#include <Model/ActionMoveTo.h>
#include <Model/ActionIdle.h>
#include <Model/Creature.h>
#include <Model/Object.h>
#include <Model/World.h>


namespace
{

  CreaturePtr findTarget(CreaturePtr i_attacker, const ObjectPtrs& i_objects, double& o_distance)
  {
    auto attackerId = i_attacker->getId();
    auto isOurObject = [&](ObjectPtr i_object)
    {
      return i_object->isCreature() && i_object->getId() != attackerId;
    };

    CreaturePtr closestTarget = nullptr;
    double distSqToClosestTarget = std::numeric_limits<double>::max();
    auto attackerPosition = xyz2xz(i_attacker->getPosition());

    for (auto objectPtr : i_objects)
    {
      if (!isOurObject(objectPtr))
        continue;

      auto targetPosition = xyz2xz(objectPtr->getPosition());
      double distSq = lengthSq(targetPosition - attackerPosition);

      if (distSq < distSqToClosestTarget)
      {
        distSq = distSqToClosestTarget;
        closestTarget = std::dynamic_pointer_cast<Creature>(objectPtr);
      }
    }

    o_distance = std::sqrt(distSqToClosestTarget);
    return closestTarget;
  }

} // anonymous NS


void CreatureController::updateObject(CreaturePtr io_creature, double i_dt,
                                    WorldController& io_worldController)
{
  auto& action = io_creature->getCurrentAction();
  switch (action.getActionType())
  {

  case ActionType::Idle:
  {
    double distanceToTarget = 0;
    auto closestTarget = findTarget(io_creature, io_worldController.getWorld().getObjects(), distanceToTarget);
    if (!closestTarget)
      break;

    const float DistanceToAttack = 1.0f;
    if (distanceToTarget <= DistanceToAttack)
      io_creature->setCurrentAction(std::make_shared<ActionAttack>(closestTarget));
    else
      io_creature->setCurrentAction(std::make_shared<ActionMoveTo>(closestTarget, 0.9f));

    break;
  }

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
