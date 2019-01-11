#pragma once

#include "IWorldController.h"

#include <Model/ModelFwd.h>
#include <Sdk/EventHandler.h>


class WorldController : public IWorldController, public EventHandler
{
public:

  WorldController(World& io_world);

  virtual void update(double i_dt) override;

  World& getWorld() { return d_world; }
  const World& getWorld() const { return d_world; }

  void addObject(ObjectPtr i_object);
  void deleteObject(ObjectId i_objectId);

private:

  World& d_world;

  ObjectPtrs d_objectsToAdd;
  std::vector<ObjectId> d_objectIdsToDelete;

  void updateScripts(double i_dt);
  void updateObjects(double i_dt);
  void addDeleteObjects();

  // Scripts

  const int MaxNumberOfCreatures = 10;
  const double TimeBeforeNextCreatureIsSpawn = 3.0;
  
  double timeLeftBeforeSpawn;
};
