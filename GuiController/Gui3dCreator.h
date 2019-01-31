#pragma once

#include <GuiModel/GuiModelFwd.h>
#include <Model/ModelFwd.h>


class Gui3dCreator
{
public:
  static std::shared_ptr<Gui3dCollection> create();

  static std::shared_ptr<CollisionShapeGui3d> createCollisionShapeGui3d(const IShape& i_shape);

private:
  Gui3dCreator() = default;
};
