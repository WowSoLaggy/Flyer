#include "stdafx.h"
#include "Gui3dCreator.h"

#include <GuiModel/CollisionShapeGui3d.h>
#include <GuiModel/Gui3dCollection.h>
#include <Model/ColCircle.h>
#include <Model/ColRect.h>
#include <Model/IColShape.h>


std::shared_ptr<Gui3dCollection> Gui3dCreator::create()
{
  return std::make_shared<Gui3dCollection>();
}


std::shared_ptr<CollisionShapeGui3d> Gui3dCreator::createCollisionShapeGui3d(const IColShape& i_shape)
{
  static const std::map<ColShapeType, std::string> shapeTextureMap =
  {
    { ColShapeType::Circle, "Circle.dds" },
    { ColShapeType::Rect, "Square.dds" },
  };
  const auto shapeType = i_shape.getColShapeType();

  auto collisionShapeGui3d = std::make_shared<CollisionShapeGui3d>();

  collisionShapeGui3d->setModelName("Tile.cmo");
  collisionShapeGui3d->setTextureName(shapeTextureMap.at(shapeType));

  switch (shapeType)
  {
  case ColShapeType::Circle:
  {
    const auto& shape = dynamic_cast<const ColCircle&>(i_shape).getCircle();
    float scale = (float)shape.getRadius() * 2;
    collisionShapeGui3d->setScale({ scale, 1.0f, scale });
    break;
  }

  case ColShapeType::Rect:
  {
    const auto& shape = dynamic_cast<const ColRect&>(i_shape).getRect();
    collisionShapeGui3d->setScale({ (float)shape.getWidth(), 1.0f, (float)shape.getHeight() });
    break;
  }
  }

  return collisionShapeGui3d;
}
