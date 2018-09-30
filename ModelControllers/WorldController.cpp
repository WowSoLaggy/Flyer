#include "stdafx.h"
#include "WorldController.h"

#include "ObjectController.h"

#include <Model/ActionHold.h>
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
  tom.setPosition({ -7.5f, -7.5f });
  tom.setModelName("Tom.obj");
  tom.setTextureName("Blank.dds");
  tom.setCurrentAction(std::make_shared<ActionHold>(ActionHold(2)));
  pWorld->getObjects().push_back(std::move(tom));

  return std::shared_ptr<World>(pWorld);
}


void WorldController::updateWorld(World& i_world, double i_dt)
{
  for (auto& object : i_world.getObjects())
    ObjectController::updateObject(object, i_dt);
}
