#pragma once

#include "IWorldController.h"

#include <Model/ModelFwd.h>
#include <Sdk/EventHandler.h>
#include <Sdk/SdkFwd.h>


class WorldController : public IWorldController, public EventHandler
{
public:

  WorldController(World& io_world);

  virtual void update(double i_dt) override;
  virtual void processInput(const KeyboardState& i_keyboardState) override;

  World& getWorld() { return d_world; }
  const World& getWorld() const { return d_world; }

  void addObject(ObjectPtr i_object);
  void deleteObject(UniqueId i_objectId);

private:

  World& d_world;

  ObjectPtrs d_objectsToAdd;
  std::vector<UniqueId> d_objectIdsToDelete;

  void updateScripts(double i_dt);
  void updateObjects(double i_dt);
  void addDeleteObjects();

  // Player

  CreaturePtr d_player;

  void findPlayer();

  // Scripts

  const int MaxNumberOfCreatures = 20;
  const double TimeBeforeNextCreatureIsSpawn = 1.0;
  
  double timeLeftBeforeSpawn;
};
