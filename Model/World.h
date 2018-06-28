#pragma once

#include "Object.h"
#include "Terrain.h"


class World
{

public:

  Terrain& getTerrain() { return d_terrain; }
  const Terrain& getTerrain() const { return d_terrain; }

  std::vector<Object>& getObjects() { return d_objects; }
  const std::vector<Object>& getObjects() const { return d_objects; }

private:

  Terrain d_terrain;
  std::vector<Object> d_objects;

};
