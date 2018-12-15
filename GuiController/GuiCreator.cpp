#include "stdafx.h"
#include "GuiCreator.h"

#include <GuiModel/GuiCollection.h>
#include <GuiModel/Label.h>


std::shared_ptr<GuiCollection> GuiCreator::createGameGui()
{
  auto guiCollection = std::make_shared<GuiCollection>();

  auto pLabel = std::make_shared<Label>();
  pLabel->setPosition({ 0, 0 });
  pLabel->setText("Meow");
  guiCollection->getGuis().push_back(pLabel);

  return guiCollection;
}
