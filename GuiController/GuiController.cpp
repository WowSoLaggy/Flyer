#include "stdafx.h"
#include "GuiController.h"

#include <GuiModel/GuiCollection.h>
#include <GuiModel/Label.h>


std::shared_ptr<GuiCollection> GuiController::createGameGui()
{
  auto guiCollection = std::make_shared<GuiCollection>();

  auto pLabel = std::make_shared<Label>();
  pLabel->setText("Meow");
  guiCollection->addGui(pLabel);

  return guiCollection;
}
