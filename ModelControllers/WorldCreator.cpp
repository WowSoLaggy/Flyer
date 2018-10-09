#include "stdafx.h"
#include "WorldCreator.h"

#include <Model/ActionHold.h>
#include <Model/HeightMap.h>
#include <Model/Object.h>
#include <Model/World.h>


namespace
{

  const int sizeX = 20;
  const int sizeZ = 20;
  const float defaultHeight = 1.0f;
  const float heightGridStep = 1.0f;

  Object createTom()
  {
    Object tom;

    tom.setPosition({ 2.5f, 2.5f });
    tom.setModelName("Tom.obj");
    tom.setTextureName("Tom.dds");
    tom.setCurrentAction(std::make_shared<ActionHold>(ActionHold(2)));

    return tom;
  }

  Object createHouse()
  {
    Object house;

    house.setPosition({ 16.5f, 6.5f });
    house.setModelName("House.obj");
    house.setTextureName("House.dds");

    return house;
  }

  HeightMap createHeightMap()
  {
    HeightMap heightMap;

    heightMap.resize(sizeX, sizeZ, defaultHeight);

    return heightMap;
  }

} // anonymous NS


std::shared_ptr<World> WorldCreator::createNewWorld()
{
  auto* pWorld = new World();

  pWorld->getTerrain().setTextureName("Grass.dds");
  pWorld->getTerrain().setHeightMap(createHeightMap());
  pWorld->getTerrain().setHeightGridStep(heightGridStep);
  
  pWorld->getObjects().push_back(createTom());
  pWorld->getObjects().push_back(createHouse());

  return std::shared_ptr<World>(pWorld);
}
