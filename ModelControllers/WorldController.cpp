#include "stdafx.h"
#include "WorldController.h"

#include <Model/World.h>


std::shared_ptr<World> WorldController::createNewWorld()
{
  auto* pWorld = new World();

  pWorld->getTerrain().setModelName("Surface.obj");
  pWorld->getTerrain().setTextureName("Grass.dds");
  pWorld->getTerrain().setSizeX(10);
  pWorld->getTerrain().setSizeZ(10);
  pWorld->getTerrain().setHeight(0);

  Object player;
  player.setPosition({ 5, 5 });
  player.setModelName("Player.obj");
  player.setTextureName("Blank.dds");
  pWorld->getObjects().push_back(std::move(player));

  return std::shared_ptr<World>(pWorld);
}


void WorldController::updateWorld(const World& i_world, double i_dt)
{
}
