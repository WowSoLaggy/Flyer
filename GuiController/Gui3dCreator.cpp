#include "stdafx.h"
#include "Gui3dCreator.h"

#include <GuiModel/CollisionShapeGui3d.h>
#include <GuiModel/Gui3dCollection.h>
#include <Model/Aabb.h>
#include <Model/Circle.h>
#include <Model/IShape.h>


std::shared_ptr<Gui3dCollection> Gui3dCreator::create()
{
  return std::make_shared<Gui3dCollection>();
}


std::shared_ptr<CollisionShapeGui3d> Gui3dCreator::createCollisionShapeGui3d(const IShape& i_shape)
{
  static const std::map<ShapeType, std::string> shapeTextureMap =
  {
    { ShapeType::Circle, "Circle.dds" },
    { ShapeType::Aabb, "Square.dds" },
  };
  const auto shapeType = i_shape.getShapeType();

  auto collisionShapeGui3d = std::make_shared<CollisionShapeGui3d>();

  collisionShapeGui3d->setModelName("Tile.cmo");
  collisionShapeGui3d->setTextureName(shapeTextureMap.at(shapeType));

  switch (shapeType)
  {
  case ShapeType::Circle:
  {
    const auto& shape = dynamic_cast<const Circle&>(i_shape);
    float scale = (float)shape.getRadius() * 2;
    collisionShapeGui3d->setScale({ scale, 1.0f, scale });
    break;
  }

  case ShapeType::Aabb:
  {
    const auto& shape = dynamic_cast<const Aabb&>(i_shape);
    collisionShapeGui3d->setScale({ (float)shape.getWidth(), 1.0f, (float)shape.getHeight() });
    break;
  }
  }

  return collisionShapeGui3d;
}
