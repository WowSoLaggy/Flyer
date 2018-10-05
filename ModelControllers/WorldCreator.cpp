#include "stdafx.h"
#include "WorldCreator.h"

#include <Model/ActionHold.h>
#include <Model/HeightMap.h>
#include <Model/Object.h>
#include <Model/World.h>


namespace
{

  const int sizeX = 20;
  const int sizeY = 20;
  const float defaultHeight = 1.0f;
  const float heightGridStep = 1.0f;

  Object createObject()
  {
    Object tom;

    tom.setPosition({ 2.5f, 2.5f });
    tom.setModelName("Tom.obj");
    tom.setTextureName("Blank.dds");
    tom.setCurrentAction(std::make_shared<ActionHold>(ActionHold(2)));

    return tom;
  }

  HeightMap createHeightMap()
  {
    HeightMap heightMap;

    heightMap.resize(sizeX, sizeY, defaultHeight);

    return heightMap;
  }

} // anonymous NS


std::shared_ptr<World> WorldCreator::createNewWorld()
{
  auto* pWorld = new World();

  pWorld->getTerrain().setTextureName("Grass.dds");
  pWorld->getTerrain().setHeightMap(createHeightMap());
  pWorld->getTerrain().setHeightGridStep(heightGridStep);
  
  pWorld->getObjects().push_back(createObject());

  return std::shared_ptr<World>(pWorld);
}
