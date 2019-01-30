#include "stdafx.h"
#include "Gui3dCreator.h"

#include <GuiModel/CollisionShapeGui3d.h>
#include <GuiModel/Gui3dCollection.h>
#include <Model/IShape.h>


std::shared_ptr<Gui3dCollection> Gui3dCreator::create()
{
  return std::make_shared<Gui3dCollection>();
}


std::shared_ptr<CollisionShapeGui3d> Gui3dCreator::createCollisionShapeGui3d(ShapeType i_shapeType)
{
  static const std::map<ShapeType, std::string> shapeTextureMap =
  {
    { ShapeType::Circle, "Circle.dds" },
    { ShapeType::Aabb, "Square.dds" },
  };

  auto collisionShapeGui3d = std::make_shared<CollisionShapeGui3d>();

  collisionShapeGui3d->setModelName("Tile.cmo");
  collisionShapeGui3d->setTextureName(shapeTextureMap.at(i_shapeType));

  return collisionShapeGui3d;
}
