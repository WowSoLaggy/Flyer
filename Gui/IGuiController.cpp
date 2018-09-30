#include "stdafx.h"
#include "IGuiController.h"

#include "GuiController.h"


std::shared_ptr<IGuiController> IGuiController::create()
{
  auto* pGuiController = new GuiController();
  return std::shared_ptr<IGuiController>(pGuiController);
}
