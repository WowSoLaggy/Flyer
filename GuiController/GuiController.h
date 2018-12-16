#pragma once

#include "IGuiController.h"

#include <GuiModel/GuiModelFwd.h>
#include <Model/ModelFwd.h>
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

  std::unordered_map<GuiId, ObjectPtr> d_healthBarMap;

  void createGameGui(const World& i_world);

  void addHealthBar(CreaturePtr i_creaturePtr);
  void deleteHealthBar(ObjectId i_objectId);
  void positionHealthBar(HealthBar& io_healthBar);
  void positionHealthBar(HealthBar& io_healthBar, CreaturePtr i_creaturePtr);
};
