#include "stdafx.h"
#include "CollisionShapeHudController.h"

#include "GuiController.h"
#include "GuiEvents.h"
#include "HudCreator.h"

#include <GuiModel/CollisionShapeHud.h>
#include <GuiModel/HudCollection.h>
#include <Model/Creature.h>


CollisionShapeHudController::CollisionShapeHudController(
  GuiController& io_guiController, HudCollection& io_hudCollection)
  : d_guiController(io_guiController)
  , d_hudCollection(io_hudCollection)
{
}


IGuiPtr CollisionShapeHudController::getGuiForCreature(UniqueId i_objectId)
{
  auto guiToObjectIt = std::find_if(d_collisionShapeHudMap.begin(), d_collisionShapeHudMap.end(),
                                    [&](const auto& pair) { return pair.second->getId() == i_objectId; });
  if (guiToObjectIt == d_collisionShapeHudMap.end())
    return nullptr;

  auto& iGuiPtrs = d_hudCollection.huds;
  auto itGui = std::find_if(iGuiPtrs.begin(), iGuiPtrs.end(),
                            [&](const auto& i_gui) { return i_gui->getId() == guiToObjectIt->first; });
  if (itGui == iGuiPtrs.end())
    return nullptr;

  return *itGui;
}


void CollisionShapeHudController::update(CollisionShapeHud& io_collisionShapeHud)
{
  auto creaturePtr = std::dynamic_pointer_cast<Creature>(d_collisionShapeHudMap.at(io_collisionShapeHud.getId()));
  positionCollisionShapeHud(io_collisionShapeHud, creaturePtr);
}


void CollisionShapeHudController::addCollisionShapeHud(ObjectPtr i_objectPtr)
{
  auto pCollisionShapeHud = HudCreator::createCollisionShapeHud();
  positionCollisionShapeHud(*pCollisionShapeHud, i_objectPtr);

  d_hudCollection.huds.push_back(pCollisionShapeHud);
  d_collisionShapeHudMap[pCollisionShapeHud->getId()] = i_objectPtr;

  d_guiController.notify(GuiAddedEvent{ pCollisionShapeHud });
}

void CollisionShapeHudController::deleteCollisionShapeHud(UniqueId i_objectId)
{
  auto guiToObjectIt = std::find_if(d_collisionShapeHudMap.begin(), d_collisionShapeHudMap.end(),
                                    [&](const auto& pair) { return pair.second->getId() == i_objectId; });
  if (guiToObjectIt == d_collisionShapeHudMap.end())
    return;

  auto& iGuiPtrs = d_hudCollection.huds;
  auto itGui = std::find_if(iGuiPtrs.begin(), iGuiPtrs.end(),
                            [&](const auto& i_gui) { return i_gui->getId() == guiToObjectIt->first; });
  if (itGui == iGuiPtrs.end())
    return;

  d_guiController.notify(GuiDeletedEvent{ *itGui });

  iGuiPtrs.erase(itGui);
  d_collisionShapeHudMap.erase(guiToObjectIt);
}

void CollisionShapeHudController::positionCollisionShapeHud(CollisionShapeHud& io_collisionShapeHud)
{
  auto objectPtr = d_collisionShapeHudMap.at(io_collisionShapeHud.getId());
  if (objectPtr->isCreature())
    positionCollisionShapeHud(io_collisionShapeHud, std::dynamic_pointer_cast<Creature>(objectPtr));
}

void CollisionShapeHudController::positionCollisionShapeHud(
  CollisionShapeHud& io_collisionShapeHud, ObjectPtr i_objectPtr)
{
  io_collisionShapeHud.setPosition(i_objectPtr->getPosition());
}
