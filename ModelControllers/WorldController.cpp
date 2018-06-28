#include "stdafx.h"
#include "WorldController.h"

#include <Model/World.h>


std::shared_ptr<World> createNewWorld()
{
  auto* pWorld = new World();

  pWorld->getTerrain().setSizeX(10);
  pWorld->getTerrain().setSizeZ(10);
  pWorld->getTerrain().setHeight(0);

  Object player;
  player.setPosition({ 5, 5 });
  pWorld->getObjects().push_back(std::move(player));

  return std::shared_ptr<World>(pWorld);
}
