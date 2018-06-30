#include "stdafx.h"
#include "Engine.h"


bool Engine::isRendererCreated() const
{
  return d_renderDevice.isCreated();
}


void Engine::createRenderer(HWND i_hWnd, int i_resolutionX, int i_resolutionY)
{
  d_renderDevice.create(i_hWnd, i_resolutionX, i_resolutionY);
}


void Engine::disposeRenderer()
{
  d_renderDevice.dispose();
}
