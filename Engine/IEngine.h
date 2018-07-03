#pragma once

#include "Callbacks.h"

#include <RenderApi/RenderApiFwd.h>


class IEngine
{
public:

  static std::shared_ptr<IEngine> create();

public:

  virtual ~IEngine() = default;

  virtual void run(
    ControlCallback i_controlCallback,
    UpdateCallback i_updateCallback,
    RenderCallback i_renderCallback) = 0;

  virtual void initialize() = 0;
  virtual void dispose() = 0;

  virtual std::shared_ptr<IRenderDevice> getRenderDevice() = 0;
  virtual bool isRendererCreated() const = 0;
  virtual void createRenderer(HWND i_hWnd, int i_resolutionX, int i_resolutionY) = 0;
  virtual void disposeRenderer() = 0;

};
