#pragma once

#include "GuiControllerFwd.h"

#include <GuiModel/GuiModelFwd.h>
#include <Model/ModelFwd.h>


class CollisionShapeHudController
{
public:
  CollisionShapeHudController(GuiController& io_guiController, HudCollection& io_hudCollection);

  void update(CollisionShapeHud& io_collisionShapeHud);

  void addCollisionShapeHud(ObjectPtr i_objectPtr);
  void deleteCollisionShapeHud(UniqueId i_objectId);
  void positionCollisionShapeHud(CollisionShapeHud& io_collisionShapeHud);
  void positionCollisionShapeHud(CollisionShapeHud& io_collisionShapeHud, ObjectPtr i_objectPtr);

private:
  GuiController& d_guiController;
  HudCollection& d_hudCollection;

  std::unordered_map<GuiId, ObjectPtr> d_collisionShapeHudMap;

  IGuiPtr getGuiForCreature(UniqueId i_objectId);
};
