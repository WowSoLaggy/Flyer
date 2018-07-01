#include "stdafx.h"
#include "Engine.h"

#include <RenderApi/IRenderDevice.h>


bool Engine::isRendererCreated() const
{
  return d_renderDevice->isInitialized();
}


void Engine::createRenderer(HWND i_hWnd, int i_resolutionX, int i_resolutionY)
{
  d_renderDevice->initialize(i_hWnd, i_resolutionX, i_resolutionY);
}


void Engine::disposeRenderer()
{
  d_renderDevice->dispose();
}
