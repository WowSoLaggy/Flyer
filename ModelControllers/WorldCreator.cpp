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
      tom.setModelName("Tom.cmo");
      tom.setCurrentAction(std::make_shared<ActionHold>(ActionHold(2)));
      o_object.push_back(std::move(tom));
    }

    {
      Object house;
      house.setPosition({ 16.5f, 1.0f, 6.5f });
      house.setRotation({ 0, Math::degToRad(-135.0f), 0 });
      house.setModelName("House.cmo");
      o_object.push_back(std::move(house));
    }

    {
      /*Object stump;
      stump.setPosition({ 8.0f, 1.0f, 12.0f });
      stump.setModelName("Stump.obj");
      o_object.push_back(std::move(stump));*/
    }

    /*{
      Object tree;
      tree.setPosition({ 11.5f, 1.0f, 6.5f });
      tree.setModelName("Tree.obj");
      o_object.push_back(std::move(tree));
    }*/

    {
      /*Object fence;
      fence.setPosition({ 12.0f, 1.0f, 5.75f });
      fence.setRotation({ 0, Math::degToRad(15.0f), 0 });
      fence.setModelName("Fence.obj");
      o_object.push_back(std::move(fence));*/
    }

    {
      /*Object fenceSouth;
      fenceSouth.setPosition({ 0.5f, 1.0f, 19.5f });
      fenceSouth.setModelName("Fence10.obj");
      fenceSouth.setTextureName("Fence.dds");
      o_object.push_back(std::move(fenceSouth));*/
    }

    {
      /*Object fenceWest;
      fenceWest.setPosition({ 0.5f, 1.0f, 19.5f });
      fenceWest.setRotation({ 0, Math::degToRad(90.0f), 0 });
      fenceWest.setModelName("Fence10.obj");
      o_object.push_back(std::move(fenceWest));*/
    }

    {
      /*Object fenceNorth;
      fenceNorth.setPosition({ 0.5f, 1.0f, 0.5f });
      fenceNorth.setModelName("Fence10.obj");
      o_object.push_back(std::move(fenceNorth));*/
    }

    {
      /*Object fenceEast;
      fenceEast.setPosition({ 19.5f, 1.0f, 19.5f });
      fenceEast.setRotation({ 0, Math::degToRad(90.0f), 0 });
      fenceEast.setModelName("Fence10.obj");
      o_object.push_back(std::move(fenceEast));*/
    }

    {
      Object arrow;
      arrow.setPosition({ 15.0f, 1.0f, 15.0f });
      arrow.setModelName("Arrow.cmo");
      o_object.push_back(std::move(arrow));
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
