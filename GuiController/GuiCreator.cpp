#include "stdafx.h"
#include "GuiCreator.h"

#include <GuiModel/GuiCollection.h>
#include <GuiModel/HealthBar.h>
#include <GuiModel/Label.h>


std::shared_ptr<GuiCollection> GuiCreator::createGameGui()
{
  auto guiCollection = std::make_shared<GuiCollection>();

  auto pLabel = std::make_shared<Label>();
  pLabel->setPosition(Vector2::zero());
  pLabel->setText("Meow");
  guiCollection->getGuis().push_back(pLabel);

  return guiCollection;
}


std::shared_ptr<HealthBar> GuiCreator::createHealthBar()
{
  auto pHealthBar = std::make_shared<HealthBar>();
  pHealthBar->setTextureBackName("HealthBar_back.dds");
  pHealthBar->setTextureFrontName("HealthBar_front.dds");
  pHealthBar->setOffset({ -40, 10 });
  pHealthBar->setFrontOffset({ 2, 2 });
  pHealthBar->setSizeBack({ 80, 8 });
  pHealthBar->setSizeFront({ 76, 4 });
  return pHealthBar;
}
