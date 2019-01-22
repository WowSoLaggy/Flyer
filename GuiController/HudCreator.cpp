#include "stdafx.h"
#include "HudCreator.h"

#include <GuiModel/CollisionShapeHud.h>
#include <GuiModel/HudCollection.h>


std::shared_ptr<HudCollection> HudCreator::createGameHud()
{
  return std::make_shared<HudCollection>();
}


std::shared_ptr<CollisionShapeHud> HudCreator::createCollisionShapeHud()
{
  auto collisionShapeHud = std::make_shared<CollisionShapeHud>();

  collisionShapeHud->setModelName("Tile.cmo");
  collisionShapeHud->setTextureName("Circle.dds");

  return collisionShapeHud;
}
