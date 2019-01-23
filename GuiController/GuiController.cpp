#include "stdafx.h"
#include "GuiController.h"

#include "GuiEvents.h"

#include <GuiModel/CollisionShapeGui3d.h>
#include <GuiModel/CurrentActionPanel.h>
#include <GuiModel/GuiCollection.h>
#include <GuiModel/Gui3dCollection.h>
#include <GuiModel/HealthBar.h>
#include <GuiModel/Label.h>
#include <GuiModel/Panel.h>
#include <Model/Creature.h>
#include <Model/Object.h>
#include <Model/World.h>
#include <ModelControllers/WorldController.h>
#include <ModelControllers/WorldEvents.h>


GuiController::GuiController(GuiCollection& io_guiCollection, Gui3dCollection& io_gui3dCollection,
                             IWorldController& io_worldController, const ICamera& i_camera)
  : d_guiCollection(io_guiCollection)
  , d_gui3dCollection(io_gui3dCollection)
  , d_labelController()
  , d_healthBarController(*this, io_guiCollection, i_camera)
  , d_currentActionPanelController(*this, io_guiCollection, i_camera)
  , d_collisionShapeGui3dController(*this, io_gui3dCollection)
{
  auto& worldController = dynamic_cast<WorldController&>(io_worldController);

  createGameGui(worldController.getWorld());

  connectTo(worldController);
}


void GuiController::update(double i_dt)
{
  for (auto gui3d : d_gui3dCollection.guis)
  {
    if (auto* pCollisionShapeGui3d = dynamic_cast<CollisionShapeGui3d*>(gui3d.get()))
      d_collisionShapeGui3dController.update(*pCollisionShapeGui3d);
  }

  for (auto gui : d_guiCollection.guis)
  {
    if (auto* pLabel = dynamic_cast<Label*>(gui.get()))
      d_labelController.update(*pLabel, i_dt);
    else if (auto* pHealthBar = dynamic_cast<HealthBar*>(gui.get()))
      d_healthBarController.update(*pHealthBar);
    else if (auto* pCurrentActionPanel = dynamic_cast<CurrentActionPanel*>(gui.get()))
      d_currentActionPanelController.update(*pCurrentActionPanel);
  }
}


void GuiController::processEvent(const IEvent& i_event)
{
  if (auto* pObjectAddedEvent = dynamic_cast<const ObjectAddedEvent*>(&i_event))
  {
    auto objectPtr = pObjectAddedEvent->getObject();
    if (objectPtr->isCreature())
    {
      d_healthBarController.addHealthBar(std::dynamic_pointer_cast<Creature>(objectPtr));
      d_currentActionPanelController.addCurrentActionPanel(std::dynamic_pointer_cast<Creature>(objectPtr));
      d_collisionShapeGui3dController.addCollisionShapeGui3d(std::dynamic_pointer_cast<Creature>(objectPtr));
    }
  }
  else if (auto* pObjectDeletedEvent = dynamic_cast<const ObjectDeletedEvent*>(&i_event))
  {
    d_healthBarController.deleteHealthBar(pObjectDeletedEvent->getObject()->getId());
    d_currentActionPanelController.deleteCurrentActionPanel(pObjectDeletedEvent->getObject()->getId());
    d_collisionShapeGui3dController.deleteCollisionShapeGui3d(pObjectDeletedEvent->getObject()->getId());
  }
  else if (auto* pObjectChangedActionEvent = dynamic_cast<const ObjectChangedActionEvent*>(&i_event))
  {
    if (auto guiPtr = d_currentActionPanelController.updateActionTexture(pObjectChangedActionEvent->getObject()))
      notify(GuiResourcesChanged{ guiPtr });
  }
}


void GuiController::createGameGui(const World& i_world)
{
  for (const auto& objectPtr : i_world.getObjects())
  {
    if (objectPtr->isCreature())
    {
      d_healthBarController.addHealthBar(std::dynamic_pointer_cast<Creature>(objectPtr));
      d_currentActionPanelController.addCurrentActionPanel(std::dynamic_pointer_cast<Creature>(objectPtr));
      d_collisionShapeGui3dController.addCollisionShapeGui3d(std::dynamic_pointer_cast<Creature>(objectPtr));
    }
  }
}
