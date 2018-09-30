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

  Object tom;
  tom.setPosition({ 5, 5 });
  tom.setModelName("Tom.obj");
  tom.setTextureName("Blank.dds");
  pWorld->getObjects().push_back(std::move(tom));

  return std::shared_ptr<World>(pWorld);
}


void WorldController::updateWorld(const World& i_world, double i_dt)
{
}
