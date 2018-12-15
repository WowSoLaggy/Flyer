#include "stdafx.h"
#include "GuiController.h"

#include "LabelController.h"

#include <GuiModel/GuiCollection.h>
#include <GuiModel/Label.h>
#include <ModelControllers/WorldController.h>
#include <ModelControllers/WorldEvents.h>
#include <RenderApi/ICamera.h>


GuiController::GuiController(GuiCollection& io_guiCollection, IWorldController& io_worldController, const ICamera& i_camera)
  : d_guiCollection(io_guiCollection)
  , d_camera(i_camera)
{
  auto& worldController = dynamic_cast<WorldController&>(io_worldController);
  connectTo(worldController);
}


void GuiController::update(double i_dt)
{
  auto& guis = d_guiCollection.getGuis();
  for (auto gui : guis)
  {
    if (auto* pLabel = dynamic_cast<Label*>(gui.get()))
      LabelController::update(*pLabel, i_dt);
  }
}


void GuiController::processEvent(const IEvent& i_event)
{
  if (auto* pObjectAddedEvent = dynamic_cast<const ObjectAddedEvent*>(&i_event))
  {
  }
  else if (auto* pObjectDeletedEvent = dynamic_cast<const ObjectDeletedEvent*>(&i_event))
  {
  }
}
