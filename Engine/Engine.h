#pragma once

#include "IEngine.h"

#include <RenderApi/RenderApiFwd.h>


class Engine : public IEngine
{
public:

  void run(ControlCallback i_controlCallback, UpdateCallback i_updateCallback) override;

  virtual void initialize() override;
  virtual void dispose() override;

  bool isRendererCreated() const override;
  void createRenderer(HWND i_hWnd, int i_resolutionX, int i_resolutionY) override;
  void disposeRenderer() override;

private:

  std::shared_ptr<IRenderDevice> d_pRenderDevice;

};
