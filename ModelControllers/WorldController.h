#pragma once

#include <Model/ModelFwd.h>
#include <Model/Object.h>
#include <ViewModel/ViewModelFwd.h>


class WorldController
{
public:

  static void updateWorld(World& io_world, double i_dt, WorldVm& i_worldVm);

  static void addObject(Object i_object);
  static void deleteObject(ObjectId i_objectId);

private:

  WorldController() = default;

  static std::vector<Object> d_objectsToAdd;
  static std::vector<ObjectId> d_objectIdsToDelete;
};
