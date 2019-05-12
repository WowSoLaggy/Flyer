#pragma once

#include "GuiControllerFwd.h"

#include <GuiModel/GuiModelFwd.h>
#include <Model/ModelFwd.h>
#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/SdkFwd.h>


class CurrentActionPanelController
{
public:
  CurrentActionPanelController(GuiController& io_guiController, GuiCollection& io_guiCollection,
                               const ICamera& i_camera);

  void update(CurrentActionPanel& io_currentActionPanel);
  IGuiPtr updateActionTexture(ObjectPtr i_objectPtr);

  void addCurrentActionPanel(ObjectPtr i_objectPtr);
  void deleteCurrentActionPanel(Sdk::UniqueId i_objectId);
  void positionCurrentActionPanel(CurrentActionPanel& io_currentActionPanel);
  void positionCurrentActionPanel(CurrentActionPanel& io_currentActionPanel, ObjectPtr i_objectPtr);

private:
  GuiController& d_guiController;
  GuiCollection& d_guiCollection;
  const ICamera& d_camera;

  std::unordered_map<GuiId, ObjectPtr> d_currentActionPanelMap;

  IGuiPtr getGuiForCreature(Sdk::UniqueId i_objectId);
};
