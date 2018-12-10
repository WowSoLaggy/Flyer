#pragma once

#include "Object.h"
#include "Terrain.h"

#include <Model/ModelFwd.h>


class World
{
public:

  Terrain& getTerrain() { return d_terrain; }
  const Terrain& getTerrain() const { return d_terrain; }

  ObjectPtrs& getObjects() { return d_objects; }
  const ObjectPtrs& getObjects() const { return d_objects; }

private:

  Terrain d_terrain;
  ObjectPtrs d_objects;

};
