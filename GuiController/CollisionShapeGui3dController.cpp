#include "stdafx.h"
#include "CollisionShapeGui3dController.h"

#include "GuiController.h"
#include "GuiEvents.h"
#include "Gui3dCreator.h"

#include <GuiModel/CollisionShapeGui3d.h>
#include <GuiModel/Gui3dCollection.h>
#include <Model/Object.h>


CollisionShapeGui3dController::CollisionShapeGui3dController(
  GuiController& io_guiController, Gui3dCollection& io_gui3dCollection)
  : d_guiController(io_guiController)
  , d_gui3dCollection(io_gui3dCollection)
{
}


IGuiPtr CollisionShapeGui3dController::getGuiForCreature(UniqueId i_objectId)
{
  auto guiToObjectIt = std::find_if(d_collisionShapeGui3dMap.begin(), d_collisionShapeGui3dMap.end(),
                                    [&](const auto& pair) { return pair.second->getId() == i_objectId; });
  if (guiToObjectIt == d_collisionShapeGui3dMap.end())
    return nullptr;

  auto& iGuiPtrs = d_gui3dCollection.guis;
  auto itGui = std::find_if(iGuiPtrs.begin(), iGuiPtrs.end(),
                            [&](const auto& i_gui) { return i_gui->getId() == guiToObjectIt->first; });
  if (itGui == iGuiPtrs.end())
    return nullptr;

  return *itGui;
}


void CollisionShapeGui3dController::update(CollisionShapeGui3d& io_collisionShapeGui3d)
{
  auto objectPtr = d_collisionShapeGui3dMap.at(io_collisionShapeGui3d.getId());
  positionCollisionShapeGui3d(io_collisionShapeGui3d, objectPtr);
}


void CollisionShapeGui3dController::addCollisionShapeGui3d(ObjectPtr i_objectPtr)
{
  auto pCollisionShapeGui3d = Gui3dCreator::createCollisionShapeGui3d();
  positionCollisionShapeGui3d(*pCollisionShapeGui3d, i_objectPtr);

  d_gui3dCollection.guis.push_back(pCollisionShapeGui3d);
  d_collisionShapeGui3dMap[pCollisionShapeGui3d->getId()] = i_objectPtr;

  d_guiController.notify(GuiAddedEvent{ pCollisionShapeGui3d });
}

void CollisionShapeGui3dController::deleteCollisionShapeGui3d(UniqueId i_objectId)
{
  auto guiToObjectIt = std::find_if(d_collisionShapeGui3dMap.begin(), d_collisionShapeGui3dMap.end(),
                                    [&](const auto& pair) { return pair.second->getId() == i_objectId; });
  if (guiToObjectIt == d_collisionShapeGui3dMap.end())
    return;

  auto& iGuiPtrs = d_gui3dCollection.guis;
  auto itGui = std::find_if(iGuiPtrs.begin(), iGuiPtrs.end(),
                            [&](const auto& i_gui) { return i_gui->getId() == guiToObjectIt->first; });
  if (itGui == iGuiPtrs.end())
    return;

  d_guiController.notify(GuiDeletedEvent{ *itGui });

  iGuiPtrs.erase(itGui);
  d_collisionShapeGui3dMap.erase(guiToObjectIt);
}

void CollisionShapeGui3dController::positionCollisionShapeGui3d(CollisionShapeGui3d& io_collisionShapeGui3d)
{
  auto objectPtr = d_collisionShapeGui3dMap.at(io_collisionShapeGui3d.getId());
  if (objectPtr->isCreature())
    positionCollisionShapeGui3d(io_collisionShapeGui3d, objectPtr);
}

void CollisionShapeGui3dController::positionCollisionShapeGui3d(
  CollisionShapeGui3d& io_collisionShapeGui3d, ObjectPtr i_objectPtr)
{
  auto position = i_objectPtr->getPosition();
  position.y += 0.1f;
  io_collisionShapeGui3d.setPosition(position);
}
