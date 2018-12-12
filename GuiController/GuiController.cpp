#include "stdafx.h"
#include "GuiController.h"

#include "LabelController.h"

#include <GuiModel/GuiCollection.h>
#include <GuiModel/Label.h>
#include <ModelControllers/WorldController.h>


GuiController::GuiController(GuiCollection& io_guiCollection, IWorldController& io_worldController)
  : d_guiCollection(io_guiCollection)
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
