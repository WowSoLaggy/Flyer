#pragma once

#include "GuiControllerFwd.h"

#include <GuiModel/GuiModelFwd.h>
#include <Model/ModelFwd.h>


class CollisionShapeGui3dController
{
public:
  CollisionShapeGui3dController(GuiController& io_guiController, Gui3dCollection& io_gui3dCollection);

  void update(CollisionShapeGui3d& io_collisionShapeGui3d);

  void addCollisionShapeGui3d(ObjectPtr i_objectPtr);
  void deleteCollisionShapeGui3d(Sdk::UniqueId i_objectId);
  void deleteAllCollisionShapes();
  void positionCollisionShapeGui3d(CollisionShapeGui3d& io_collisionShapeGui3d, ObjectPtr i_objectPtr);

private:
  GuiController& d_guiController;
  Gui3dCollection& d_gui3dCollection;

  std::unordered_map<GuiId, ObjectPtr> d_collisionShapeGui3dMap;

  IGuiPtr getGuiForCreature(Sdk::UniqueId i_objectId);
};
