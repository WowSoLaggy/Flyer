#include "stdafx.h"
#include "WorldController.h"

#include "ObjectController.h"
#include "WorldEvents.h"

#include <Model/World.h>


WorldController::WorldController(World& io_world)
  : d_world(io_world)
{
}


void WorldController::update(double i_dt)
{
  updateObjects(i_dt);
  addDeleteObjects();
}


void WorldController::addObject(ObjectPtr i_object)
{
  d_objectsToAdd.push_back(i_object);
}

void WorldController::deleteObject(ObjectId i_objectId)
{
  d_objectIdsToDelete.push_back(i_objectId);
}


void WorldController::updateObjects(double i_dt)
{
  for (auto& object : d_world.getObjects())
    ObjectController::updateObject(object, i_dt, *this);
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

      notify(ObjectDeletedEvent{ **it });

      worldObjects.erase(it);
    }
    d_objectIdsToDelete.clear();
  }

  if (!d_objectsToAdd.empty())
  {
    int size = (int)worldObjects.size();
    worldObjects.insert(worldObjects.end(), d_objectsToAdd.begin(), d_objectsToAdd.end());

    for (auto object : d_objectsToAdd)
      notify(ObjectAddedEvent{ *object });

    d_objectsToAdd.clear();
  }
}
