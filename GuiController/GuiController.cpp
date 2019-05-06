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
#include <Model/ObjectConverters.h>
#include <Model/World.h>
#include <ModelControllers/WorldController.h>
#include <ModelControllers/WorldEvents.h>


GuiController::GuiController(GuiCollection& io_guiCollection, Gui3dCollection& io_gui3dCollection,
                             IWorldController& io_worldController, const ICamera& i_camera)
  : d_worldController(dynamic_cast<WorldController&>(io_worldController))
  , d_guiCollection(io_guiCollection)
  , d_gui3dCollection(io_gui3dCollection)
  , d_labelController()
  , d_healthBarController(*this, io_guiCollection, i_camera)
  , d_currentActionPanelController(*this, io_guiCollection, i_camera)
  , d_collisionShapeGui3dController(*this, io_gui3dCollection)
  , d_showCollisionShapes(false)
{
  createGameGui();
  connectTo(d_worldController);
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


void GuiController::switchShowCollisionShapes()
{
  d_showCollisionShapes = !d_showCollisionShapes;
  if (d_showCollisionShapes)
    createCollisionShapes();
  else
    deleteCollisionShapes();
}


void GuiController::processEvent(const Sdk::IEvent& i_event)
{
  if (auto* pObjectAddedEvent = dynamic_cast<const ObjectAddedEvent*>(&i_event))
  {
    auto objectPtr = pObjectAddedEvent->getObject();

    if (objectPtr->isCreature())
    {
      d_healthBarController.addHealthBar(castObjectToCreature(objectPtr));
      d_currentActionPanelController.addCurrentActionPanel(castObjectToCreature(objectPtr));
    }

    if (d_showCollisionShapes && objectPtr->hasCollisionShape())
      d_collisionShapeGui3dController.addCollisionShapeGui3d(objectPtr);
  }
  else if (auto* pObjectDeletedEvent = dynamic_cast<const ObjectDeletedEvent*>(&i_event))
  {
    d_healthBarController.deleteHealthBar(pObjectDeletedEvent->getObject()->getId());
    d_currentActionPanelController.deleteCurrentActionPanel(pObjectDeletedEvent->getObject()->getId());

    if (d_showCollisionShapes)
      d_collisionShapeGui3dController.deleteCollisionShapeGui3d(pObjectDeletedEvent->getObject()->getId());
  }
  else if (auto* pObjectChangedActionEvent = dynamic_cast<const ObjectChangedActionEvent*>(&i_event))
  {
    if (auto guiPtr = d_currentActionPanelController.updateActionTexture(pObjectChangedActionEvent->getObject()))
      notify(GuiResourcesChanged{ guiPtr });
  }
}


void GuiController::createCollisionShapes()
{
  for (const auto& objectPtr : d_worldController.getWorld().getObjects())
  {
    if (objectPtr->hasCollisionShape())
      d_collisionShapeGui3dController.addCollisionShapeGui3d(objectPtr);
  }
}

void GuiController::deleteCollisionShapes()
{
  d_collisionShapeGui3dController.deleteAllCollisionShapes();
}


void GuiController::createGameGui()
{
  for (const auto& objectPtr : d_worldController.getWorld().getObjects())
  {
    if (objectPtr->isCreature())
    {
      d_healthBarController.addHealthBar(castObjectToCreature(objectPtr));
      d_currentActionPanelController.addCurrentActionPanel(castObjectToCreature(objectPtr));
    }
  }

  if (d_showCollisionShapes)
    createCollisionShapes();
}
