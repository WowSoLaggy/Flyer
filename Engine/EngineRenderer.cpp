#include "stdafx.h"
#include "Engine.h"

#include "IResourceController.h"

#include <RenderApi/IRenderDevice.h>


std::shared_ptr<IRenderDevice> Engine::getRenderDevice()
{
  return d_renderDevice;
}

std::shared_ptr<IResourceController> Engine::getResourceController()
{
  return d_resourceController;
}


bool Engine::isRendererCreated() const
{
  return d_renderDevice->isInitialized();
}


void Engine::createRenderer(HWND i_hWnd, int i_resolutionX, int i_resolutionY)
{
  d_renderDevice->initialize(i_hWnd, i_resolutionX, i_resolutionY);
  d_resourceController->loadResources();
}


void Engine::disposeRenderer()
{
  d_resourceController->unloadResources();
  d_renderDevice->dispose();
}
