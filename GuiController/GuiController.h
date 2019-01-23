#pragma once

#include "CollisionShapeGui3dController.h"
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

  GuiController(GuiCollection& io_guiCollection, Gui3dCollection& io_gui3dCollection,
                IWorldController& io_worldController, const ICamera& i_camera);

  virtual void update(double i_dt) override;

  virtual void processEvent(const IEvent& i_event) override;

  GuiCollection& getGuiCollection() { return d_guiCollection; }
  const GuiCollection& getGuiCollection() const { return d_guiCollection; }

  Gui3dCollection& getGui3dCollection() { return d_gui3dCollection; }
  const Gui3dCollection& getGui3dCollection() const { return d_gui3dCollection; }

private:

  GuiCollection& d_guiCollection;
  Gui3dCollection& d_gui3dCollection;

  LabelController d_labelController;
  HealthBarController d_healthBarController;
  CurrentActionPanelController d_currentActionPanelController;
  CollisionShapeGui3dController d_collisionShapeGui3dController;

  void createGameGui(const World& i_world);
};
