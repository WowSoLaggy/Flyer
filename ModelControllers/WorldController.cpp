#include "stdafx.h"
#include "WorldController.h"

#include "CreatureController.h"
#include "PhysicsController.h"
#include "WorldCreator.h"
#include "WorldEvents.h"

#include <Model/Creature.h>
#include <Model/World.h>


WorldController::WorldController(World& io_world)
  : d_world(io_world)
{
  timeLeftBeforeSpawn = TimeBeforeNextCreatureIsSpawn;
}


void WorldController::update(double i_dt)
{
  updateScripts(i_dt);
  updateObjects(i_dt);
  addDeleteObjects();

  PhysicsController::updateObjects(d_world.getObjects(), i_dt);
}


void WorldController::addObject(ObjectPtr i_object)
{
  d_objectsToAdd.push_back(i_object);
}

void WorldController::deleteObject(UniqueId i_objectId)
{
  d_objectIdsToDelete.push_back(i_objectId);
}


void WorldController::updateScripts(double i_dt)
{
  if (!d_world.getScriptsActive())
    return;

  auto& worldObjects = d_world.getObjects();
  int numberOfAliveCreatures = std::accumulate(worldObjects.begin(), worldObjects.end(), 0,
                  [](int i_total, const ObjectPtr& i_objectPtr)
  {
    return i_objectPtr->isCreature() ? i_total + 1 : i_total;
  });

  if (numberOfAliveCreatures >= MaxNumberOfCreatures)
    return;

  timeLeftBeforeSpawn -= i_dt;
  if (timeLeftBeforeSpawn > 0)
    return;

  timeLeftBeforeSpawn = TimeBeforeNextCreatureIsSpawn;

  CreaturePtr newCreature = WorldCreator::createCreature();
  float xPos = (float)(std::rand() % 100 + 20) / 10;
  float zPos = (float)(std::rand() % 160 + 20) / 10;
  newCreature->setPosition({ xPos, 1.0f, zPos });
  addObject(newCreature);
}

void WorldController::updateObjects(double i_dt)
{
  for (auto objectPtr : d_world.getObjects())
  {
    if (objectPtr->isCreature())
      CreatureController::updateCreature(std::dynamic_pointer_cast<Creature>(objectPtr), i_dt, *this);
  }
}

void WorldController::addDeleteObjects()
{
  auto& worldObjects = d_world.getObjects();

  if (!d_objectIdsToDelete.empty())
  {
    for (auto objectId : d_objectIdsToDelete)
    {
      auto it = std::find_if(worldObjects.begin(), worldObjects.end(),
                             [&](const ObjectPtr& i_object) { return i_object->getId() == objectId; });
      if (it == worldObjects.end())
        continue;

      notify(ObjectDeletedEvent{ *it });

      worldObjects.erase(it);
    }
    d_objectIdsToDelete.clear();
  }

  if (!d_objectsToAdd.empty())
  {
    int size = (int)worldObjects.size();
    worldObjects.insert(worldObjects.end(), d_objectsToAdd.begin(), d_objectsToAdd.end());

    for (auto object : d_objectsToAdd)
      notify(ObjectAddedEvent{ object });

    d_objectsToAdd.clear();
  }
}
