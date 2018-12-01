#include "stdafx.h"
#include "WorldController.h"

#include "ObjectController.h"

#include <Model/World.h>
#include <ViewModel/WorldVm.h>


std::vector<Object> WorldController::d_objectsToAdd;
std::vector<ObjectId> WorldController::d_objectIdsToDelete;


void WorldController::updateWorld(World& io_world, double i_dt, WorldVm& i_worldVm)
{
  auto& objs = io_world.getObjects();

  for (auto& object : objs)
    ObjectController::updateObject(object, i_dt);

  for (auto objectId : d_objectIdsToDelete)
  {
    i_worldVm.onObjectDeleted(objectId);
    objs.erase(std::remove_if(objs.begin(), objs.end(),
      [&](const Object& i_object) { return i_object.getId() == objectId; }), objs.end());
  }
  d_objectIdsToDelete.clear();

  int size = objs.size();
  objs.insert(objs.end(), d_objectsToAdd.begin(), d_objectsToAdd.end());
  auto it = std::next(objs.begin(), size);
  for (; it != objs.end(); ++it)
    i_worldVm.onObjectAdded(*it);
  d_objectsToAdd.clear();
}


void WorldController::addObject(Object i_object)
{
  d_objectsToAdd.push_back(i_object);
}

void WorldController::deleteObject(ObjectId i_objectId)
{
  d_objectIdsToDelete.push_back(i_objectId);
}
