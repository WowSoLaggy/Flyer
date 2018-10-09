#include "stdafx.h"
#include "WorldCreator.h"

#include <Model/ActionHold.h>
#include <Model/HeightMap.h>
#include <Model/Object.h>
#include <Model/World.h>
#include <Sdk/Math.h>


namespace
{

  const int sizeX = 20;
  const int sizeZ = 20;
  const float defaultHeight = 1.0f;
  const float heightGridStep = 1.0f;

  void createObjects(std::vector<Object>& o_object)
  {
    o_object.clear();

    {
      Object tom;
      tom.setPosition({ 2.5f, 1.0f, 2.5f });
      tom.setModelName("Tom.obj");
      tom.setTextureName("Tom.dds");
      tom.setCurrentAction(std::make_shared<ActionHold>(ActionHold(2)));
      o_object.push_back(std::move(tom));
    }

    {
      Object house;
      house.setPosition({ 16.5f, 1.0f, 6.5f });
      house.setRotation({ 0, Math::degToRad(-135.0f), 0 });
      house.setModelName("House.obj");
      house.setTextureName("House.dds");
      o_object.push_back(std::move(house));
    }

    {
      Object stump;
      stump.setPosition({ 8.0f, 1.0f, 12.0f });
      stump.setModelName("Stump.obj");
      stump.setTextureName("Stump.dds");
      o_object.push_back(std::move(stump));
    }
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
  
  createObjects(pWorld->getObjects());

  return std::shared_ptr<World>(pWorld);
}
