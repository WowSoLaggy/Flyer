#pragma once

#include "EngineFwd.h"
#include "IEngine.h"

#include <RenderApi/RenderApiFwd.h>


class Engine : public IEngine
{
public:

  void run(
    ControlCallback i_controlCallback,
    UpdateCallback i_updateCallback,
    RenderCallback i_renderCallback) override;

  virtual void initialize(const std::string& i_resourceFolder) override;
  virtual void dispose() override;

  std::shared_ptr<IRenderDevice> getRenderDevice() override;
  std::shared_ptr<IResourceController> getResourceController() override;

  bool isRendererCreated() const override;
  void createRenderer(HWND i_hWnd, int i_resolutionX, int i_resolutionY) override;
  void disposeRenderer() override;

private:

  std::shared_ptr<IRenderDevice> d_renderDevice;
  std::shared_ptr<IResourceController> d_resourceController;

};
