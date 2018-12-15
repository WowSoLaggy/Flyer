#include "stdafx.h"
#include "IGuiController.h"

#include "GuiController.h"


std::shared_ptr<IGuiController> IGuiController::create(
  GuiCollection& io_guiCollection, IWorldController& io_worldController, const ICamera& i_camera)
{
  return std::shared_ptr<IGuiController>(new GuiController(io_guiCollection, io_worldController, i_camera));
}
