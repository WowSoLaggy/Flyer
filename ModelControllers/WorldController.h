#pragma once

#include "IWorldController.h"

#include <Model/ModelFwd.h>
#include <LaggySdk/EventHandler.h>
#include <LaggySdk/SdkFwd.h>


class WorldController : public IWorldController, public Sdk::EventHandler
{
public:

  WorldController(World& io_world);

  virtual void update(double i_dt) override;
  virtual void processInput(const Dx::KeyboardState& i_keyboardState) override;

  World& getWorld() { return d_world; }
  const World& getWorld() const { return d_world; }

  void addObject(ObjectPtr i_object);
  void deleteObject(Sdk::UniqueId i_objectId);

  CreaturePtr getPlayer() { return d_player; }
  const CreaturePtr& getPlayer() const { return d_player; }

private:

  World& d_world;

  ObjectPtrs d_objectsToAdd;
  std::vector<Sdk::UniqueId> d_objectIdsToDelete;

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
