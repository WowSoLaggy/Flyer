#pragma once

#include <GuiModel/GuiModelFwd.h>
#include <ModelControllers/ModelControllersFwd.h>


class IGuiController
{
public:

  static std::shared_ptr<IGuiController> create(
    GuiCollection& io_guiCollection, IWorldController& io_worldController);

public:

  virtual ~IGuiController() = default;

  virtual void update(double i_dt) = 0;
};
