#pragma once

#include "Object.h"
#include "Terrain.h"

#include <Model/ModelFwd.h>


class World
{
public:

  World();

  bool getScriptsActive() const { return d_scriptsActive; }
  void setScriptsActive(bool i_scriptsActive) { d_scriptsActive = i_scriptsActive; }

  Terrain& getTerrain() { return d_terrain; }
  const Terrain& getTerrain() const { return d_terrain; }

  ObjectPtrs& getObjects() { return d_objects; }
  const ObjectPtrs& getObjects() const { return d_objects; }

private:

  bool d_scriptsActive;

  Terrain d_terrain;
  ObjectPtrs d_objects;

};
