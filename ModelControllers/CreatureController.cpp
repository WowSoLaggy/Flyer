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
        distSqToClosestTarget = distSq;
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
  const float AttackDistance = 1.0f;
  const float ApproachDistance = AttackDistance - 0.1f;

  double attackCooldownValue = std::max(io_creature->getPropAttackCooldown().getValue() - i_dt, 0.0);
  io_creature->getPropAttackCooldown().setValue(attackCooldownValue);

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
    auto position = io_creature->getPosition();
    Vector2 position2 = { position.x, position.z };
    auto goal = moveToAction.getGoal();

    auto direction = goal - position2;

    if (lengthSq(direction) <= moveToAction.getToleranceSq())
    {
      double timeToHold = (double)(std::rand() % 50) / 10;
      io_creature->setCurrentAction(std::make_shared<ActionIdle>());
      break;
    }

    const float maxSpeed = 1.0f;
    auto movement = normalize(direction) * maxSpeed * (float)i_dt;

    io_creature->setPosition(io_creature->getPosition() + Vector3{ movement.x, 0, movement.y });
    io_creature->setRotation({ 0, -std::atan2(direction.y, direction.x), 0 });

    break;
  }

  case ActionType::Attack:
  {
    const auto& attackAction = dynamic_cast<const ActionAttack&>(action);
    auto targetObjectPtr = attackAction.getTarget();

    auto positionAttacker = xyz2xz(io_creature->getPosition());
    auto positionTarget = xyz2xz(targetObjectPtr->getPosition());
    
    auto distanceToTarget = length(positionTarget - positionAttacker);

    if (distanceToTarget > AttackDistance)
    {
      io_creature->setCurrentAction(std::make_shared<ActionMoveTo>(targetObjectPtr, ApproachDistance));
      break;
    }

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
