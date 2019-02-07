#pragma once

#include "ViewModelFwd.h"

#include <GuiController/GuiControllerFwd.h>
#include <GuiModel/GuiModelFwd.h>
#include <ModelControllers/ModelControllersFwd.h>
#include <RenderApi/RenderApiFwd.h>


class GameVm
{
public:

  GameVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController,
         IWorldController& i_worldController,
         int i_screenWidth, int i_screenHeight);

  ICamera& getCamera() { return *d_camera; }
  const ICamera& getCamera() const { return *d_camera; }

  void buildGuiVms(IGuiController& i_guiController);

  void render(double i_dt) const;

private:

  IRenderDevice& d_renderDevice;
  const IResourceController& d_resourceController;
  WorldController& d_worldController;

  std::shared_ptr<ICamera> d_camera;
  std::shared_ptr<IRenderer2d> d_renderer2d;
  std::shared_ptr<IRenderer3d> d_renderer3d;

  std::shared_ptr<WorldVm> d_worldVm;
  std::shared_ptr<GuiCollectionVm> d_guiCollectionVm;

};
