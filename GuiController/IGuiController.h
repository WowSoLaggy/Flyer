#pragma once

#include <GuiModel/GuiModelFwd.h>
#include <ModelControllers/ModelControllersFwd.h>
#include <RenderApi/RenderApiFwd.h>

#include <memory>


class IGuiController
{
public:

  static std::shared_ptr<IGuiController> create(
    GuiCollection& io_guiCollection, Gui3dCollection& io_gui3dCollection,
    IWorldController& io_worldController, const ICamera& i_camera);

public:

  virtual ~IGuiController() = default;

  virtual void update(double i_dt) = 0;

  virtual void switchShowCollisionShapes() = 0;
};
