#include "stdafx.h"
#include "WorldCreator.h"

#include <Model/ActionMoveTo.h>
#include <Model/Creature.h>
#include <Model/ColCircle.h>
#include <Model/ColRect.h>
#include <Model/HeightMap.h>
#include <Model/Object.h>
#include <Model/World.h>
#include <LaggySdk/Math.h>


namespace
{
  using namespace std::literals;

  const int SizeX = 1;
  const int SizeZ = 1;
  const float DefaultHeight = 1.0f;
  const float HeightGridStep = 100.0f;

  const auto DefaultTerrainTexture = "Sand.dds"s;

  const auto DefaultModelName = "Character.cmo"s;

  const float DefaultCreatureCollisionShapeRadius = 0.5f;
  const Sdk::Vector3 DefaultCreatureRotation{ Sdk::degToRad(-90.0f), 0, 0 };
  const float DefaultCreatureScaleCoef = 0.6f;
  const Sdk::Vector3 DefaultCreatureScaleVector{
    DefaultCreatureScaleCoef, DefaultCreatureScaleCoef, DefaultCreatureScaleCoef };

  const ControlledBy DefaultControlledBy = ControlledBy::None;

  const bool DefaultCreatureMovable = true;
  const float DefaultAcceleration = 20.0f;
  const float DefaultMaxSpeed = 4.0f;

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

  return pWorld;
}


CreaturePtr WorldCreator::createCreature()
{
  CreaturePtr creature = std::make_shared<Creature>();

  creature->setMovable(DefaultCreatureMovable);
  creature->setAcceleration(DefaultAcceleration);
  creature->setMaxSpeed(DefaultMaxSpeed);

  creature->setModelName(DefaultModelName);
  creature->setCollisionShape(std::make_shared<ColCircle>(DefaultCreatureCollisionShapeRadius));

  creature->setRotation(DefaultCreatureRotation);
  creature->setScale(DefaultCreatureScaleVector);

  creature->setControlledBy(DefaultControlledBy);

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
    auto maximus = createCreature(objects);
    maximus->setPosition({ 50.0f, 1.0f, 50.0f });
    maximus->setControlledBy(ControlledBy::Player);
  }

  {
    auto marcus = createCreature(objects);
    marcus->setPosition({ 55.0f, 1.0f, 55.0f });
  }

  {
    auto house = createObject(objects);
    house->setPosition({ 50.0f, 1.0f, 50.0f });
    house->setModelName("Arena.cmo");

    const float scale = 0.004f;
    house->setScale({ scale, scale, scale });
  }
}
