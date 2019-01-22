#include "stdafx.h"
#include "HudCreator.h"

#include <GuiModel/HudCollection.h>


std::shared_ptr<HudCollection> HudCreator::createGameHud()
{
  auto hudCollection = std::make_shared<HudCollection>();
  return hudCollection;
}
