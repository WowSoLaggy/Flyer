#include "stdafx.h"
#include "GuiController.h"


void GuiController::initialize()
{
}

void GuiController::dispose()
{
  removeAllGuis();
}


void GuiController::removeAllGuis()
{
  d_guis.clear();
}
