#pragma once

#include "IGuiController.h"

#include <GuiModel/GuiModelFwd.h>
#include <ModelControllers/ModelControllersFwd.h>
#include <Sdk/EventHandler.h>


class GuiController : public IGuiController, public EventHandler
{
public:

  GuiController(GuiCollection& io_guiCollection, IWorldController& io_worldController, const ICamera& i_camera);

  virtual void update(double i_dt) override;

  virtual void processEvent(const IEvent& i_event) override;

  GuiCollection& getCollection() { return d_guiCollection; }
  const GuiCollection& getCollection() const { return d_guiCollection; }

private:

  GuiCollection& d_guiCollection;
  const ICamera& d_camera;

};
