#include "stdafx.h"
#include "Engine.h"

#include <LaggyDx/IRenderDevice.h>
#include <LaggyDx/IResourceController.h>


std::shared_ptr<Dx::IRenderDevice> Engine::getRenderDevice()
{
  return d_renderDevice;
}

std::shared_ptr<Dx::IResourceController> Engine::getResourceController()
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
  d_resourceController->loadResources(*d_renderDevice);
}


void Engine::disposeRenderer()
{
  d_resourceController->unloadResources();
  d_renderDevice->dispose();
}
