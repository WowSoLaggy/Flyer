#include "stdafx.h"
#include "WorldController.h"

#include "ObjectController.h"

#include <Model/World.h>
#include <ViewModel/WorldVm.h>


ObjectPtrs WorldController::d_objectsToAdd;
std::vector<ObjectId> WorldController::d_objectIdsToDelete;


void WorldController::updateWorld(World& io_world, double i_dt, WorldVm& i_worldVm)
{
  updateObjects(io_world.getObjects(), i_dt);
  addDeleteObjects(io_world.getObjects(), i_worldVm);
}


void WorldController::addObject(ObjectPtr i_object)
{
  d_objectsToAdd.push_back(i_object);
}

void WorldController::deleteObject(ObjectId i_objectId)
{
  d_objectIdsToDelete.push_back(i_objectId);
}


void WorldController::updateObjects(ObjectPtrs& io_worldObjects, double i_dt)
{
  for (auto& object : io_worldObjects)
    ObjectController::updateObject(object, i_dt);
}

void WorldController::addDeleteObjects(ObjectPtrs& io_worldObjects, WorldVm& i_worldVm)
{
  if (!d_objectIdsToDelete.empty())
  {
    for (auto objectId : d_objectIdsToDelete)
    {
      i_worldVm.onObjectDeleted(objectId);
      io_worldObjects.erase(
        std::remove_if(io_worldObjects.begin(), io_worldObjects.end(),
                       [&](const ObjectPtr& i_object) { return i_object->getId() == objectId; }),
        io_worldObjects.end());
    }
    d_objectIdsToDelete.clear();
  }

  if (!d_objectsToAdd.empty())
  {
    int size = (int)io_worldObjects.size();
    io_worldObjects.insert(io_worldObjects.end(), d_objectsToAdd.begin(), d_objectsToAdd.end());
    auto it = std::next(io_worldObjects.begin(), size);
    for (; it != io_worldObjects.end(); ++it)
      i_worldVm.onObjectAdded(**it);
    d_objectsToAdd.clear();
  }
}
