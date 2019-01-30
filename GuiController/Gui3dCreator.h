#pragma once

#include <GuiModel/GuiModelFwd.h>
#include <Model/ModelFwd.h>


class Gui3dCreator
{
public:
  static std::shared_ptr<Gui3dCollection> create();

  static std::shared_ptr<CollisionShapeGui3d> createCollisionShapeGui3d(ShapeType i_shapeType);

private:
  Gui3dCreator() = default;
};
