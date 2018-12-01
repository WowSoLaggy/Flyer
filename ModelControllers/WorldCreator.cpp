#include "stdafx.h"
#include "WorldCreator.h"

#include <Model/ActionHold.h>
#include <Model/HeightMap.h>
#include <Model/Object.h>
#include <Model/World.h>
#include <Sdk/Math.h>


namespace
{

  const int sizeX = 1;
  const int sizeZ = 1;
  const float defaultHeight = 1.0f;
  const float heightGridStep = 20.0f;

  void createObjects(std::vector<Object>& o_objects)
  {
    o_objects.clear();

    {
      Object tom;
      tom.setPosition({ 2.5f, 1.0f, 2.5f });
      tom.setModelName("Tom.cmo");
      tom.setCurrentAction(std::make_shared<ActionHold>(ActionHold(2)));
      o_objects.push_back(std::move(tom));
    }

    {
      Object house;
      house.setPosition({ 16.5f, 1.0f, 6.5f });
      house.setRotation({ 0, Math::degToRad(-135.0f), 0 });
      house.setModelName("House.cmo");
      o_objects.push_back(std::move(house));
    }

    {
      Object tree;
      tree.setPosition({ 11.5f, 1.0f, 6.5f });
      tree.setModelName("Tree.cmo");
      o_objects.push_back(std::move(tree));
    }

    {
      Object fence;
      fence.setPosition({ 12.0f, 1.0f, 5.75f });
      fence.setRotation({ 0, Math::degToRad(105.0f), 0 });
      fence.setModelName("Fence.cmo");
      o_objects.push_back(std::move(fence));
    }

    {
      Object fenceSouth;
      fenceSouth.setPosition({ 0.5f, 1.0f, 19.5f });
      fenceSouth.setRotation({ 0, Math::degToRad(90.0f), 0 });
      fenceSouth.setModelName("Fence10.cmo");
      o_objects.push_back(std::move(fenceSouth));
    }

    {
      Object fenceWest;
      fenceWest.setPosition({ 0.5f, 1.0f, 19.5f });
      fenceWest.setRotation({ 0, Math::degToRad(180.0f), 0 });
      fenceWest.setModelName("Fence10.cmo");
      o_objects.push_back(std::move(fenceWest));
    }

    {
      Object fenceNorth;
      fenceNorth.setPosition({ 0.5f, 1.0f, 0.5f });
      fenceNorth.setRotation({ 0, Math::degToRad(90.0f), 0 });
      fenceNorth.setModelName("Fence10.cmo");
      o_objects.push_back(std::move(fenceNorth));
    }

    {
      Object fenceEast;
      fenceEast.setPosition({ 19.5f, 1.0f, 19.5f });
      fenceEast.setRotation({ 0, Math::degToRad(180.0f), 0 });
      fenceEast.setModelName("Fence10.cmo");
      o_objects.push_back(std::move(fenceEast));
    }

    {
      Object arrow;
      arrow.setPosition({ 15.0f, 1.0f, 15.0f });
      arrow.setModelName("Arrow.cmo");
      o_objects.push_back(std::move(arrow));
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
