#pragma once

#include "IGuiController.h"

#include <GuiModel/GuiModelFwd.h>
#include <ModelControllers/ModelControllersFwd.h>
#include <Sdk/EventHandler.h>


class GuiController : public IGuiController, public EventHandler
{
public:

  GuiController(GuiCollection& io_guiCollection, IWorldController& io_worldController);

  virtual void update(double i_dt) override;

  virtual void processEvent(const IEvent& i_event) override;

private:

  GuiCollection& d_guiCollection;
};
