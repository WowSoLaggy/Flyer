#pragma once

#include "Callbacks.h"


class IEngine
{
public:

  static std::shared_ptr<IEngine> createEngine();

public:

  virtual void run(ControlCallback i_controlCallback, UpdateCallback i_updateCallback) = 0;


  virtual bool isRendererCreated() const = 0;
  virtual void createRenderer(HWND i_hWnd, int i_resolutionX, int i_resolutionY) = 0;
  virtual void disposeRenderer() = 0;

};
