#include "stdafx.h"
#include "WorldCreator.h"

#include <Model/ActionMoveTo.h>
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

  const bool DefaultAiControlled = true;

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
  
  pWorld->getObjects().clear();

  //createArena(*pWorld);
  createCollisionTest(*pWorld);

  return pWorld;
}


CreaturePtr WorldCreator::createCreature()
{
  CreaturePtr creature = std::make_shared<Creature>();

  creature->setModelName(defaultModelName);

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
  auto& objects = io_world.getObjects();

  {
    auto tom = createCreature(objects);
    tom->setPosition({ 2.5f, 1.0f, 2.5f });
  }

  {
    auto jerry = createCreature(objects);
    jerry->setPosition({ 8.5f, 1.0f, 12.5f });
    jerry->setRotation({ 0, Math::degToRad(180.0f), 0 });
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
    fence->setPosition({ 12.0f, 1.0f, 5.75f });
    fence->setRotation({ 0, Math::degToRad(105.0f), 0 });
    fence->setModelName("Fence.cmo");
  }

  {
    auto fenceSouth = createObject(objects);
    fenceSouth->setPosition({ 0.5f, 1.0f, 19.5f });
    fenceSouth->setRotation({ 0, Math::degToRad(90.0f), 0 });
    fenceSouth->setModelName("Fence10.cmo");
  }

  {
    auto fenceWest = createObject(objects);
    fenceWest->setPosition({ 0.5f, 1.0f, 19.5f });
    fenceWest->setRotation({ 0, Math::degToRad(180.0f), 0 });
    fenceWest->setModelName("Fence10.cmo");
  }

  {
    auto fenceNorth = createObject(objects);
    fenceNorth->setPosition({ 0.5f, 1.0f, 0.5f });
    fenceNorth->setRotation({ 0, Math::degToRad(90.0f), 0 });
    fenceNorth->setModelName("Fence10.cmo");
  }

  {
    auto fenceEast = createObject(objects);
    fenceEast->setPosition({ 19.5f, 1.0f, 19.5f });
    fenceEast->setRotation({ 0, Math::degToRad(180.0f), 0 });
    fenceEast->setModelName("Fence10.cmo");
  }
}

void WorldCreator::createCollisionTest(World& io_world)
{
  io_world.setScriptsActive(false);

  auto& objects = io_world.getObjects();

  // Opposite ones

  {
    auto testCreature1 = createCreature(objects);
    testCreature1->setPosition({ 6.5f, 1.0f, 12.5f });
    testCreature1->setAiControlled(false);
    testCreature1->setCurrentAction(std::make_shared<ActionMoveTo>(Vector2{ 12.5f, 12.5f }));
  }

  {
    auto testCreature1 = createCreature(objects);
    testCreature1->setPosition({ 10.5f, 1.0f, 12.5f });
    testCreature1->setRotation({ 0, Math::degToRad(180.0f), 0 });
    testCreature1->setAiControlled(false);
    testCreature1->setCurrentAction(std::make_shared<ActionMoveTo>(Vector2{ 4.5f, 12.5f }));
  }

  // Not opposite

  {
    auto testCreature2 = createCreature(objects);
    testCreature2->setPosition({ 6.5f, 1.0f, 14.6f });
    testCreature2->setAiControlled(false);
    testCreature2->setCurrentAction(std::make_shared<ActionMoveTo>(Vector2{ 12.5f, 14.6f }));
  }

  {
    auto testCreature2 = createCreature(objects);
    testCreature2->setPosition({ 10.5f, 1.0f, 14.5f });
    testCreature2->setRotation({ 0, Math::degToRad(180.0f), 0 });
    testCreature2->setAiControlled(false);
    testCreature2->setCurrentAction(std::make_shared<ActionMoveTo>(Vector2{ 4.5f, 14.5f }));
  }

  // "Go to a fence" creatures

  {
    auto testCreatureFence1 = createCreature(objects);
    testCreatureFence1->setPosition({ 3.0f, 1.0f, 8.0f });
    testCreatureFence1->setAiControlled(false);
    testCreatureFence1->setCurrentAction(std::make_shared<ActionMoveTo>(Vector2{ -3.0f, 2.0f }));
  }

  {
    auto testCreatureFence2 = createCreature(objects);
    testCreatureFence2->setPosition({ 3.0f, 1.0f, 4.0f });
    testCreatureFence2->setAiControlled(false);
    testCreatureFence2->setCurrentAction(std::make_shared<ActionMoveTo>(Vector2{ -3.0f, -2.0f }));
  }

  // Rest of the world

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
    fence->setPosition({ 12.0f, 1.0f, 5.75f });
    fence->setRotation({ 0, Math::degToRad(105.0f), 0 });
    fence->setModelName("Fence.cmo");
  }

  {
    auto fenceSouth = createObject(objects);
    fenceSouth->setPosition({ 0.5f, 1.0f, 19.5f });
    fenceSouth->setRotation({ 0, Math::degToRad(90.0f), 0 });
    fenceSouth->setModelName("Fence10.cmo");
  }

  {
    auto fenceWest = createObject(objects);
    fenceWest->setPosition({ 0.5f, 1.0f, 19.5f });
    fenceWest->setRotation({ 0, Math::degToRad(180.0f), 0 });
    fenceWest->setModelName("Fence10.cmo");
  }

  {
    auto fenceNorth = createObject(objects);
    fenceNorth->setPosition({ 0.5f, 1.0f, 0.5f });
    fenceNorth->setRotation({ 0, Math::degToRad(90.0f), 0 });
    fenceNorth->setModelName("Fence10.cmo");
  }

  {
    auto fenceEast = createObject(objects);
    fenceEast->setPosition({ 19.5f, 1.0f, 19.5f });
    fenceEast->setRotation({ 0, Math::degToRad(180.0f), 0 });
    fenceEast->setModelName("Fence10.cmo");
  }
}
