#pragma once

#include "Callbacks.h"

#include <RenderApi/RenderDevice.h>


class Engine
{
public:

  void run(ControlCallback i_controlCallback, UpdateCallback i_updateCallback);


  bool isRendererCreated() const;
  void createRenderer(HWND i_hWnd, int i_resolutionX, int i_resolutionY);
  void disposeRenderer();

private:

  RenderDevice d_renderDevice;

};
