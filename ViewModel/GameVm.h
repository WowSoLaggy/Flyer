#pragma once

#include "ViewModelFwd.h"

#include <GuiModel/GuiModelFwd.h>
#include <Model/ModelFwd.h>
#include <RenderApi/RenderApiFwd.h>


class GameVm
{
public:

  GameVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController,
    int i_screenWidth, int i_screenHeight);

  ICamera& getCamera() { return *d_camera; }
  const ICamera& getCamera() const { return *d_camera; }

  void buildWorldVms(const World& i_world);
  void buildGuiVms(const GuiCollection& i_guiCollection);

  void render(double i_dt) const;

private:

  IRenderDevice& d_renderDevice;
  const IResourceController& d_resourceController;

  std::shared_ptr<ICamera> d_camera;
  std::shared_ptr<IRenderer2d> d_renderer2d;
  std::shared_ptr<IRenderer3d> d_renderer3d;

  std::shared_ptr<WorldVm> d_worldVm;
  std::shared_ptr<GuiCollectionVm> d_guiCollectionVm;

};
