#pragma once

#include <GuiController/GuiControllerFwd.h>
#include <GuiModel/GuiModelFwd.h>
#include <Model/ModelFwd.h>
#include <RenderApi/RenderApiFwd.h>
#include <LaggySdk/SdkFwd.h>


class HealthBarController
{
public:

  HealthBarController(GuiController& io_guiController, GuiCollection& io_guiCollection,
                      const ICamera& i_camera);

  void update(HealthBar& io_healthBar);

  void addHealthBar(CreaturePtr i_creaturePtr);
  void deleteHealthBar(Sdk::UniqueId i_objectId);
  void positionHealthBar(HealthBar& io_healthBar);
  void positionHealthBar(HealthBar& io_healthBar, CreaturePtr i_creaturePtr);

private:
  
  GuiController& d_guiController;
  GuiCollection& d_guiCollection;
  const ICamera& d_camera;

  std::unordered_map<GuiId, ObjectPtr> d_healthBarMap;
};
