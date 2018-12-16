#include "stdafx.h"
#include "GuiController.h"

#include "GuiCreator.h"
#include "GuiEvents.h"

#include <GuiModel/GuiCollection.h>
#include <GuiModel/HealthBar.h>
#include <GuiModel/Label.h>
#include <GuiModel/Panel.h>
#include <Model/Creature.h>
#include <Model/Object.h>
#include <Model/World.h>
#include <ModelControllers/WorldController.h>
#include <ModelControllers/WorldEvents.h>
#include <RenderApi/ICamera.h>


GuiController::GuiController(GuiCollection& io_guiCollection, IWorldController& io_worldController, const ICamera& i_camera)
  : d_guiCollection(io_guiCollection)
  , d_camera(i_camera)
  , d_labelController()
{
  auto& worldController = dynamic_cast<WorldController&>(io_worldController);
  createGameGui(worldController.getWorld());
  connectTo(worldController);
}


void GuiController::update(double i_dt)
{
  auto& guis = d_guiCollection.getGuis();
  for (auto gui : guis)
  {
    if (auto* pLabel = dynamic_cast<Label*>(gui.get()))
      d_labelController.update(*pLabel, i_dt);
    if (auto* pHealthBar = dynamic_cast<HealthBar*>(gui.get()))
      positionHealthBar(*pHealthBar);
  }
}


void GuiController::processEvent(const IEvent& i_event)
{
  if (auto* pObjectAddedEvent = dynamic_cast<const ObjectAddedEvent*>(&i_event))
  {
    auto objectPtr = pObjectAddedEvent->getObject();
    if (objectPtr->isCreature())
      addHealthBar(std::dynamic_pointer_cast<Creature>(objectPtr));
  }
  else if (auto* pObjectDeletedEvent = dynamic_cast<const ObjectDeletedEvent*>(&i_event))
  {
    deleteHealthBar(pObjectDeletedEvent->getObject()->getId());
  }
}


void GuiController::createGameGui(const World& i_world)
{
  for (const auto& objectPtr : i_world.getObjects())
  {
    if (objectPtr->isCreature())
      addHealthBar(std::dynamic_pointer_cast<Creature>(objectPtr));
  }
}


void GuiController::addHealthBar(CreaturePtr i_creaturePtr)
{
  auto pHealthBar = GuiCreator::createHealthBar();
  positionHealthBar(*pHealthBar, i_creaturePtr);

  d_guiCollection.getGuis().push_back(pHealthBar);
  d_healthBarMap[pHealthBar->getId()] = i_creaturePtr;

  notify(GuiAddedEvent{ pHealthBar });
}

void GuiController::deleteHealthBar(ObjectId i_objectId)
{
  auto guiToObjectIt = std::find_if(d_healthBarMap.begin(), d_healthBarMap.end(),
                                    [&](const auto& pair) { return pair.second->getId() == i_objectId; });
  if (guiToObjectIt == d_healthBarMap.end())
    return;

  auto& iGuiPtrs = d_guiCollection.getGuis();
  auto itGui = std::find_if(iGuiPtrs.begin(), iGuiPtrs.end(),
                            [&](const auto& i_gui) { return i_gui->getId() == guiToObjectIt->first; });
  if (itGui == iGuiPtrs.end())
    return;

  notify(GuiDeletedEvent{ *itGui });

  iGuiPtrs.erase(itGui);
  d_healthBarMap.erase(guiToObjectIt);
}

void GuiController::positionHealthBar(HealthBar& io_healthBar)
{
  auto objectPtr = d_healthBarMap.at(io_healthBar.getId());
  if (objectPtr->isCreature())
    positionHealthBar(io_healthBar, std::dynamic_pointer_cast<Creature>(objectPtr));
}

void GuiController::positionHealthBar(HealthBar& io_healthBar, CreaturePtr i_creaturePtr)
{
  auto pos = d_camera.worldToScreen(i_creaturePtr->getPosition());
  io_healthBar.setPosition(pos);
}

