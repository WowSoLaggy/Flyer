#include "stdafx.h"
#include "CreatureController.h"

#include "WorldController.h"

#include <Model/ActionMoveTo.h>
#include <Model/Creature.h>
#include <Model/Object.h>
#include <Model/World.h>


namespace
{
  std::map<ObjectId, ObjectId> s_destinationArrowIdMap;

  void createDestinationArrowObject(ObjectId& o_destinationArrowId, const Vector3& i_position,
                                    WorldController& io_worldController)
  {
    ObjectPtr arrow = std::make_shared<Object>();
    arrow->setPosition(i_position);
    arrow->setModelName("Arrow.cmo");

    o_destinationArrowId = arrow->getId();
    io_worldController.addObject(arrow);
  }

  void deleteDestinationArrowObject(ObjectId i_destinationArrowId, WorldController& io_worldController)
  {
    io_worldController.deleteObject(i_destinationArrowId);
  }

} // anonymous NS


void CreatureController::updateObject(CreaturePtr io_creature, double i_dt,
                                    WorldController& io_worldController)
{
  auto& action = io_creature->getCurrentAction();
  switch (action.getActionType())
  {
  /*case ActionType::Hold:
  {
    auto& holdAction = dynamic_cast<ActionHold&>(action);
    if (!holdAction.hold(i_dt))
    {
      float newX = (float)(std::rand() % 100 + 20) / 10;
      float newY = (float)(std::rand() % 160 + 20) / 10;
      io_creature->setCurrentAction(std::make_shared<ActionMoveTo>(ActionMoveTo({ newX, newY })));
      
      createDestinationArrowObject(s_destinationArrowIdMap[io_creature->getId()], { newX, 1, newY },
                                   io_worldController);
    }
    break;
  }*/

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

      //deleteDestinationArrowObject(s_destinationArrowIdMap.at(io_creature->getId()), io_worldController);

      return;
    }

    const float maxSpeed = 1.0f;
    auto movement = normalize(direction) * maxSpeed * (float)i_dt;

    io_creature->setPosition(io_creature->getPosition() + Vector3{ movement.x, 0, movement.y });
    io_creature->setRotation({ 0, -std::atan2(direction.y, direction.x), 0 });

    break;
  }

  } // switch
}
