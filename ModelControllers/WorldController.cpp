#include "stdafx.h"
#include "WorldController.h"

#include "ObjectController.h"
#include "WorldEvents.h"
#include "WorldWrapper.h"


ObjectPtrs WorldController::d_objectsToAdd;
std::vector<ObjectId> WorldController::d_objectIdsToDelete;


void WorldController::updateWorld(WorldWrapper& io_world, double i_dt)
{
  updateObjects(io_world, i_dt);
  addDeleteObjects(io_world);
}


void WorldController::addObject(ObjectPtr i_object)
{
  d_objectsToAdd.push_back(i_object);
}

void WorldController::deleteObject(ObjectId i_objectId)
{
  d_objectIdsToDelete.push_back(i_objectId);
}


void WorldController::updateObjects(WorldWrapper& io_world, double i_dt)
{
  for (auto& object : io_world.getObjects())
    ObjectController::updateObject(object, i_dt);
}

void WorldController::addDeleteObjects(WorldWrapper& io_world)
{
  auto& worldObjects = io_world.getObjects();

  if (!d_objectIdsToDelete.empty())
  {
    for (auto objectId : d_objectIdsToDelete)
    {
      auto it = std::find_if(worldObjects.begin(), worldObjects.end(),
                             [&](const ObjectPtr& i_object) { return i_object->getId() == objectId; });
      if (it == worldObjects.end())
        continue;

      io_world.notify(ObjectDeletedEvent{ **it });

      worldObjects.erase(it);
    }
    d_objectIdsToDelete.clear();
  }

  if (!d_objectsToAdd.empty())
  {
    int size = (int)worldObjects.size();
    worldObjects.insert(worldObjects.end(), d_objectsToAdd.begin(), d_objectsToAdd.end());

    for (auto object : d_objectsToAdd)
      io_world.notify(ObjectAddedEvent{ *object });

    d_objectsToAdd.clear();
  }
}
