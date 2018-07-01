#pragma once

#include "IEngine.h"

#include <RenderApi/RenderApiFwd.h>


class Engine : public IEngine
{
public:

  void run(ControlCallback i_controlCallback, UpdateCallback i_updateCallback);


  bool isRendererCreated() const;
  void createRenderer(HWND i_hWnd, int i_resolutionX, int i_resolutionY);
  void disposeRenderer();

private:

  std::shared_ptr<IRenderDevice> d_pRenderDevice;

};
