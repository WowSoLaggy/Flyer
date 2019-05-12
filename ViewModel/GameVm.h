#pragma once

#include "ViewModelFwd.h"

#include <GuiController/GuiControllerFwd.h>
#include <GuiModel/GuiModelFwd.h>
#include <ModelControllers/ModelControllersFwd.h>
#include <LaggyDx/LaggyDxFwd.h>


class GameVm
{
public:

  GameVm(Dx::IRenderDevice& io_renderDevice, const Dx::IResourceController& i_resourceController,
         IWorldController& i_worldController,
         int i_screenWidth, int i_screenHeight);

  Dx::ICamera& getCamera() { return *d_camera; }
  const Dx::ICamera& getCamera() const { return *d_camera; }

  void buildGuiVms(IGuiController& i_guiController);

  void update(double i_dt) const;
  void render(double i_dt) const;

private:

  Dx::IRenderDevice& d_renderDevice;
  const Dx::IResourceController& d_resourceController;
  WorldController& d_worldController;

  std::shared_ptr<Dx::ICamera> d_camera;
  std::shared_ptr<Dx::IRenderer2d> d_renderer2d;
  std::shared_ptr<Dx::IRenderer3d> d_renderer3d;

  std::shared_ptr<WorldVm> d_worldVm;
  std::shared_ptr<GuiCollectionVm> d_guiCollectionVm;

};
