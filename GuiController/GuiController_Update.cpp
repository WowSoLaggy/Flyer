#include "stdafx.h"
#include "GuiController.h"

#include "LabelController.h"

#include <GuiModel/GuiCollection.h>
#include <GuiModel/Label.h>


void GuiController::update(std::shared_ptr<GuiCollection> io_guiCollection, double i_dt)
{
  auto& guis = io_guiCollection->getGuis();
  for (auto gui : guis)
  {
    if (auto* pLabel = dynamic_cast<Label*>(gui.get()))
      LabelController::update(*pLabel, i_dt);
  }
}
