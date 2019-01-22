#pragma once

#include "CollisionShapeHudController.h"
#include "CurrentActionPanelController.h"
#include "HealthBarController.h"
#include "IGuiController.h"
#include "LabelController.h"

#include <GuiModel/GuiModelFwd.h>
#include <Model/ModelFwd.h>
#include <ModelControllers/ModelControllersFwd.h>
#include <Sdk/EventHandler.h>


class GuiController : public IGuiController, public EventHandler
{
public:

  GuiController(GuiCollection& io_guiCollection, HudCollection& io_hudCollection,
                IWorldController& io_worldController, const ICamera& i_camera);

  virtual void update(double i_dt) override;

  virtual void processEvent(const IEvent& i_event) override;

  GuiCollection& getGuiCollection() { return d_guiCollection; }
  const GuiCollection& getGuiCollection() const { return d_guiCollection; }

  HudCollection& getHudCollection() { return d_hudCollection; }
  const HudCollection& getHudCollection() const { return d_hudCollection; }

private:

  GuiCollection& d_guiCollection;
  HudCollection& d_hudCollection;

  LabelController d_labelController;
  HealthBarController d_healthBarController;
  CurrentActionPanelController d_currentActionPanelController;
  CollisionShapeHudController d_collisionShapeHudController;

  void createGameGui(const World& i_world);
};
