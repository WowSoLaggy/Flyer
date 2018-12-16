#include "stdafx.h"
#include "GuiCreator.h"

#include <GuiModel/GuiCollection.h>
#include <GuiModel/HealthBar.h>
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


std::shared_ptr<HealthBar> GuiCreator::createHealthBar()
{
  auto pHealthBar = std::make_shared<HealthBar>();
  pHealthBar->setTextureBackName("HealthBar_back.dds");
  pHealthBar->setTextureFrontName("HealthBar_front.dds");
  pHealthBar->setOffset({ 2, 2 });
  return pHealthBar;
}
