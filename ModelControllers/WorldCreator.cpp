#include "stdafx.h"
#include "WorldCreator.h"

#include <Model/ActionMoveTo.h>
#include <Model/Creature.h>
#include <Model/ColCircle.h>
#include <Model/ColRect.h>
#include <Model/HeightMap.h>
#include <Model/Object.h>
#include <Model/World.h>
#include <Sdk/Math.h>


namespace
{
  using namespace std::literals;

  const int SizeX = 1;
  const int SizeZ = 1;
  const float DefaultHeight = 1.0f;
  const float HeightGridStep = 20.0f;

  const auto DefaultTerrainTexture = "Sand.dds"s;

  const auto DefaultModelName = "Tom.cmo"s;

  const bool DefaultAiControlled = true;

  const bool DefaultCreatureMovable = true;
  const float DefaultAcceleration = 10.0f;
  const float DefaultMaxSpeed = 2.0f;

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

  pWorld->getTerrain().setTextureName(DefaultTerrainTexture);
  pWorld->getTerrain().setHeightMap(createHeightMap());
  pWorld->getTerrain().setHeightGridStep(HeightGridStep);
  
  pWorld->getObjects().clear();

  createArena(*pWorld);
  //createCollisionTest(*pWorld);

  return pWorld;
}


CreaturePtr WorldCreator::createCreature()
{
  CreaturePtr creature = std::make_shared<Creature>();

  creature->setMovable(DefaultCreatureMovable);
  creature->setAcceleration(DefaultAcceleration);
  creature->setMaxSpeed(DefaultMaxSpeed);

  creature->setModelName(DefaultModelName);
  creature->setCollisionShape(std::make_shared<ColCircle>(0.5f));

  creature->setAiControlled(DefaultAiControlled);

  creature->getPropHealth().set(DefaultStartHealth, DefaultMinHealth, DefaultMaxHealth);
  creature->getPropAttackCooldown().set(
    DefaultStartAttackCooldown, DefaultMinAttackCooldown, DefaultMaxAttackCooldown);
  creature->getPropDamage().set(DefaultDamage, DefaultDamage, DefaultDamage);

  return creature;
}


ObjectPtr WorldCreator::createObject(ObjectPtrs& o_objects)
{
  ObjectPtr object = std::make_shared<Object>();
  o_objects.push_back(object);
  return object;
}

CreaturePtr WorldCreator::createCreature(ObjectPtrs& o_objects)
{
  auto creature = createCreature();
  o_objects.push_back(creature);
  return creature;
}


void WorldCreator::createArena(World& io_world)
{
  io_world.setScriptsActive(false);

  auto& objects = io_world.getObjects();

  {
    auto player = createCreature(objects);
    player->setPosition({ 10.0f, 1.0f, 10.0f });
    player->setAiControlled(false);
  }

  {
    auto house = createObject(objects);
    house->setPosition({ 16.5f, 1.0f, 6.5f });
    house->setRotation({ 0, Math::degToRad(-135.0f), 0 });
    house->setModelName("House.cmo");
  }

  {
    auto tree = createObject(objects);
    tree->setPosition({ 11.5f, 1.0f, 6.5f });
    tree->setModelName("Tree.cmo");
  }

  {
    auto fence = createObject(objects);
    fence->setPosition({ 12.7f, 1.0f, 5.7f });
    fence->setRotation({ 0, Math::degToRad(15.0f), 0 });

    fence->setModelName("Fence.cmo");
    fence->setCollisionShape(std::make_shared<ColRect>(2.2f, 0.5f));
  }

  {
    auto fenceSouth = createObject(objects);
    fenceSouth->setPosition({ 10.0f, 1.0f, 19.5f });
    fenceSouth->setRotation({ 0, Math::degToRad(0.0f), 0 });

    fenceSouth->setModelName("Fence10.cmo");
    fenceSouth->setCollisionShape(std::make_shared<ColRect>(19.0f, 0.5f));
  }

  {
    auto fenceNorth = createObject(objects);
    fenceNorth->setPosition({ 10.0f, 1.0f, 0.5f });
    fenceNorth->setRotation({ 0, Math::degToRad(180.0f), 0 });

    fenceNorth->setModelName("Fence10.cmo");
    fenceNorth->setCollisionShape(std::make_shared<ColRect>(19.0f, 0.5f));
  }

  {
    auto fenceWest = createObject(objects);
    fenceWest->setPosition({ 0.5f, 1.0f, 10.0f });
    fenceWest->setRotation({ 0, Math::degToRad(-90.0f), 0 });

    fenceWest->setModelName("Fence10.cmo");
    fenceWest->setCollisionShape(std::make_shared<ColRect>(19.0f, 0.5f));
  }

  {
    auto fenceEast = createObject(objects);
    fenceEast->setPosition({ 19.5f, 1.0f, 10.0f });
    fenceEast->setRotation({ 0, Math::degToRad(90.0f), 0 });

    fenceEast->setModelName("Fence10.cmo");
    fenceEast->setCollisionShape(std::make_shared<ColRect>(19.0f, 0.5f));
  }
}
