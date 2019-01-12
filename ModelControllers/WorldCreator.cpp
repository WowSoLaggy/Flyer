#include "stdafx.h"
#include "WorldCreator.h"

#include <Model/Creature.h>
#include <Model/HeightMap.h>
#include <Model/Object.h>
#include <Model/World.h>
#include <Sdk/Math.h>


namespace
{

  const int SizeX = 1;
  const int SizeZ = 1;
  const float DefaultHeight = 1.0f;
  const float HeightGridStep = 20.0f;

  const std::string defaultModelName = "Tom.cmo";

  const int DefaultMinHealth = 0;
  const int DefaultMaxHealth = 100;
  const int DefaultStartHealth = DefaultMaxHealth;

  const double DefaultMinAttackCooldown = 0;
  const double DefaultMaxAttackCooldown = 1.0;
  const double DefaultStartAttackCooldown = DefaultMinAttackCooldown;

  const int DefaultDamage = 10;

  HeightMap createHeightMap()
  {
    HeightMap heightMap;

    heightMap.resize(SizeX, SizeZ, DefaultHeight);

    return heightMap;
  }

} // anonymous NS


std::shared_ptr<World> WorldCreator::createNewWorld()
{
  auto pWorld = std::make_shared<World>();

  pWorld->getTerrain().setTextureName("Grass.dds");
  pWorld->getTerrain().setHeightMap(createHeightMap());
  pWorld->getTerrain().setHeightGridStep(HeightGridStep);
  
  createObjects(pWorld->getObjects());

  return pWorld;
}


CreaturePtr WorldCreator::createCreature()
{
  CreaturePtr creature = std::make_shared<Creature>();

  creature->setModelName(defaultModelName);

  creature->getPropHealth().set(DefaultStartHealth, DefaultMinHealth, DefaultMaxHealth);
  creature->getPropAttackCooldown().set(
    DefaultStartAttackCooldown, DefaultMinAttackCooldown, DefaultMaxAttackCooldown);
  creature->getPropDamage().set(DefaultDamage, DefaultDamage, DefaultDamage);

  return creature;
}


void WorldCreator::createObjects(ObjectPtrs& o_objects)
{
  o_objects.clear();

  {
    CreaturePtr tom = createCreature();
    tom->setPosition({ 2.5f, 1.0f, 2.5f });

    tom->getPropHealth().setValue(100);

    o_objects.push_back(std::move(tom));
  }

  {
    CreaturePtr jerry = createCreature();
    jerry->setPosition({ 8.5f, 1.0f, 12.5f });
    jerry->setRotation({ 0, Math::degToRad(180.0f), 0 });

    jerry->getPropHealth().setValue(50);

    o_objects.push_back(std::move(jerry));
  }

  {
    ObjectPtr house = std::make_shared<Object>();
    house->setPosition({ 16.5f, 1.0f, 6.5f });
    house->setRotation({ 0, Math::degToRad(-135.0f), 0 });
    house->setModelName("House.cmo");
    o_objects.push_back(std::move(house));
  }

  {
    ObjectPtr tree = std::make_shared<Object>();
    tree->setPosition({ 11.5f, 1.0f, 6.5f });
    tree->setModelName("Tree.cmo");
    o_objects.push_back(std::move(tree));
  }

  {
    ObjectPtr fence = std::make_shared<Object>();
    fence->setPosition({ 12.0f, 1.0f, 5.75f });
    fence->setRotation({ 0, Math::degToRad(105.0f), 0 });
    fence->setModelName("Fence.cmo");
    o_objects.push_back(std::move(fence));
  }

  {
    ObjectPtr fenceSouth = std::make_shared<Object>();
    fenceSouth->setPosition({ 0.5f, 1.0f, 19.5f });
    fenceSouth->setRotation({ 0, Math::degToRad(90.0f), 0 });
    fenceSouth->setModelName("Fence10.cmo");
    o_objects.push_back(std::move(fenceSouth));
  }

  {
    ObjectPtr fenceWest = std::make_shared<Object>();
    fenceWest->setPosition({ 0.5f, 1.0f, 19.5f });
    fenceWest->setRotation({ 0, Math::degToRad(180.0f), 0 });
    fenceWest->setModelName("Fence10.cmo");
    o_objects.push_back(std::move(fenceWest));
  }

  {
    ObjectPtr fenceNorth = std::make_shared<Object>();
    fenceNorth->setPosition({ 0.5f, 1.0f, 0.5f });
    fenceNorth->setRotation({ 0, Math::degToRad(90.0f), 0 });
    fenceNorth->setModelName("Fence10.cmo");
    o_objects.push_back(std::move(fenceNorth));
  }

  {
    ObjectPtr fenceEast = std::make_shared<Object>();
    fenceEast->setPosition({ 19.5f, 1.0f, 19.5f });
    fenceEast->setRotation({ 0, Math::degToRad(180.0f), 0 });
    fenceEast->setModelName("Fence10.cmo");
    o_objects.push_back(std::move(fenceEast));
  }
}
