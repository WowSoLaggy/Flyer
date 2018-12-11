#pragma once

#include "ModelControllersFwd.h"

#include <Model/ModelFwd.h>
#include <Model/Object.h>


class WorldController
{
public:

  static void updateWorld(WorldWrapper& io_world, double i_dt);

  static void addObject(ObjectPtr i_object);
  static void deleteObject(ObjectId i_objectId);

private:

  WorldController() = default;

  static ObjectPtrs d_objectsToAdd;
  static std::vector<ObjectId> d_objectIdsToDelete;

  static void updateObjects(WorldWrapper& io_world, double i_dt);
  static void addDeleteObjects(WorldWrapper& io_world);
};
