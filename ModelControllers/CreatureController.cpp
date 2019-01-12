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

  const float AttackDistance = 1.0f;
  const float ApproachDistance = AttackDistance - 0.1f;

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
        distSqToClosestTarget = distSq;
        closestTarget = std::dynamic_pointer_cast<Creature>(objectPtr);
      }
    }

    o_distance = std::sqrt(distSqToClosestTarget);
    return closestTarget;
  }

} // anonymous NS


void CreatureController::updateCreature(CreaturePtr io_creature, double i_dt,
                                        WorldController& io_worldController)
{
  updateCreatureState(io_creature, i_dt);
  selectCreatureAction(io_creature, io_worldController);
  performCreatureAction(io_creature);
}


void CreatureController::updateCreatureState(CreaturePtr io_creature, double i_dt)
{
  double attackCooldownValue = std::max(io_creature->getPropAttackCooldown().getValue() - i_dt, 0.0);
  io_creature->getPropAttackCooldown().setValue(attackCooldownValue);
}

void CreatureController::selectCreatureAction(CreaturePtr io_creature, WorldController& io_worldController)
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

    if (distanceToTarget <= AttackDistance)
      io_creature->setCurrentAction(std::make_shared<ActionAttack>(closestTarget));
    else
      io_creature->setCurrentAction(std::make_shared<ActionMoveTo>(closestTarget, ApproachDistance));

    break;
  }

  case ActionType::MoveTo:
  {
    const auto& moveToAction = dynamic_cast<const ActionMoveTo&>(action);

    auto position = xyz2xz(io_creature->getPosition());
    auto goal = moveToAction.getGoal();
    auto direction = goal - position;

    if (lengthSq(direction) <= moveToAction.getToleranceSq())
    {
      double timeToHold = (double)(std::rand() % 50) / 10;
      io_creature->setCurrentAction(std::make_shared<ActionIdle>());
      io_creature->resetMovementDirection();
      break;
    }

    break;
  }

  case ActionType::Attack:
  {
    const auto& attackAction = dynamic_cast<const ActionAttack&>(action);
    auto targetObjectPtr = attackAction.getTarget();

    auto distance = xyz2xz(targetObjectPtr->getPosition()) - xyz2xz(io_creature->getPosition());
    auto distanceLength = length(distance);

    if (distanceLength > AttackDistance)
    {
      io_creature->setCurrentAction(std::make_shared<ActionMoveTo>(targetObjectPtr, ApproachDistance));
      break;
    }

    // TODO: Make this check not so stupid
    if (targetObjectPtr->getPropHealth().getValueRelative() < 0.01)
    {
      io_worldController.deleteObject(targetObjectPtr->getId());
      io_creature->setCurrentAction(std::make_shared<ActionIdle>());
    }

    break;
  }

  } // switch (action.getActionType())
}

void CreatureController::performCreatureAction(CreaturePtr io_creature)
{
  auto& action = io_creature->getCurrentAction();
  switch (action.getActionType())
  {

  case ActionType::Idle:
  {
    // Do nothing
    break;
  }

  case ActionType::MoveTo:
  {
    const auto& moveToAction = dynamic_cast<const ActionMoveTo&>(action);

    auto position = xyz2xz(io_creature->getPosition());
    auto goal = moveToAction.getGoal();
    auto direction = goal - position;

    io_creature->setMovementDirection({ direction.x, 0.0f, direction.y });
    io_creature->setRotation({ 0, -std::atan2(direction.y, direction.x), 0 });

    break;
  }

  case ActionType::Attack:
  {
    const auto& attackAction = dynamic_cast<const ActionAttack&>(action);
    auto targetObjectPtr = attackAction.getTarget();

    auto distance = xyz2xz(targetObjectPtr->getPosition()) - xyz2xz(io_creature->getPosition());

    // Turn to the target
    io_creature->setRotation({ 0, -std::atan2(distance.y, distance.x), 0 });

    // TODO: Make this check not so stupid
    if (io_creature->getPropAttackCooldown().getValueRelative() < 0.01)
    {
      io_creature->getPropAttackCooldown().setToMax();

      auto currentHealth = targetObjectPtr->getPropHealth().getValue();
      auto damage = io_creature->getPropDamage().getValue();

      targetObjectPtr->getPropHealth().setValue(currentHealth - damage);
    }

    break;
  }

  } // switch (action.getActionType())
}
