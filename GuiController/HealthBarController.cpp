#include "stdafx.h"
#include "HealthBarController.h"

#include "GuiController.h"
#include "GuiCreator.h"
#include "GuiEvents.h"

#include <GuiModel/GuiCollection.h>
#include <GuiModel/HealthBar.h>
#include <Model/Creature.h>
#include <Model/ObjectConverters.h>
#include <RenderApi/ICamera.h>


HealthBarController::HealthBarController(GuiController& io_guiController, GuiCollection& io_guiCollection,
                                         const ICamera& i_camera)
  : d_guiController(io_guiController)
  , d_guiCollection(io_guiCollection)
  , d_camera(i_camera)
{
}


void HealthBarController::update(HealthBar& io_healthBar)
{
  auto creaturePtr = castObjectToCreature(d_healthBarMap.at(io_healthBar.getId()));
  io_healthBar.setValue(creaturePtr->getPropHealth().getValueRelative());
  
  positionHealthBar(io_healthBar, creaturePtr);
}


void HealthBarController::addHealthBar(CreaturePtr i_creaturePtr)
{
  auto pHealthBar = GuiCreator::createHealthBar();
  positionHealthBar(*pHealthBar, i_creaturePtr);

  d_guiCollection.guis.push_back(pHealthBar);
  d_healthBarMap[pHealthBar->getId()] = i_creaturePtr;

  d_guiController.notify(GuiAddedEvent{ pHealthBar });
}

void HealthBarController::deleteHealthBar(Sdk::UniqueId i_objectId)
{
  auto guiToObjectIt = std::find_if(d_healthBarMap.begin(), d_healthBarMap.end(),
                                    [&](const auto& pair) { return pair.second->getId() == i_objectId; });
  if (guiToObjectIt == d_healthBarMap.end())
    return;

  auto& iGuiPtrs = d_guiCollection.guis;
  auto itGui = std::find_if(iGuiPtrs.begin(), iGuiPtrs.end(),
                            [&](const auto& i_gui) { return i_gui->getId() == guiToObjectIt->first; });
  if (itGui == iGuiPtrs.end())
    return;

  d_guiController.notify(GuiDeletedEvent{ *itGui });

  iGuiPtrs.erase(itGui);
  d_healthBarMap.erase(guiToObjectIt);
}

void HealthBarController::positionHealthBar(HealthBar& io_healthBar)
{
  auto objectPtr = d_healthBarMap.at(io_healthBar.getId());
  if (objectPtr->isCreature())
    positionHealthBar(io_healthBar, castObjectToCreature(objectPtr));
}

void HealthBarController::positionHealthBar(HealthBar& io_healthBar, CreaturePtr i_creaturePtr)
{
  auto pos = d_camera.worldToScreen(i_creaturePtr->getPosition());
  io_healthBar.setPosition(pos);
}
