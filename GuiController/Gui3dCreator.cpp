#include "stdafx.h"
#include "Gui3dCreator.h"

#include <GuiModel/CollisionShapeGui3d.h>
#include <GuiModel/Gui3dCollection.h>


std::shared_ptr<Gui3dCollection> Gui3dCreator::create()
{
  return std::make_shared<Gui3dCollection>();
}


std::shared_ptr<CollisionShapeGui3d> Gui3dCreator::createCollisionShapeGui3d()
{
  auto collisionShapeGui3d = std::make_shared<CollisionShapeGui3d>();

  collisionShapeGui3d->setModelName("Tile.cmo");
  collisionShapeGui3d->setTextureName("Circle.dds");

  return collisionShapeGui3d;
}
