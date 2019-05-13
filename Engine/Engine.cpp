#include "stdafx.h"
#include "Engine.h"

#include <LaggyDx/IInputDevice.h>
#include <LaggyDx/IRenderDevice.h>
#include <LaggyDx/IResourceController.h>
#include <LaggySdk/Timer.h>


void Engine::run(
  ControlCallback i_controlCallback,
  UpdateCallback i_updateCallback,
  RenderCallback i_renderCallback,
  InputCallback i_inputCallback)
{
  Sdk::Timer timer;
  timer.start();
  double dt = 0;

  while (i_controlCallback() == ControlSignal::Run)
  {
    dt = timer.restart();

    i_inputCallback(dt, d_inputDevice->check());
    i_updateCallback(dt);

    if (d_renderDevice->isInitialized())
    {
      d_renderDevice->beginScene();

      i_renderCallback(dt);

      d_renderDevice->endScene();
    }
  }
}


void Engine::initialize(const std::string& i_resourceFolder)
{
  d_renderDevice = Dx::IRenderDevice::create();

  d_resourceController = Dx::IResourceController::create();
  d_resourceController->initialize(i_resourceFolder);

  d_inputDevice = Dx::IInputDevice::create();
  d_inputDevice->initialize();
}

void Engine::dispose()
{
  d_inputDevice->dispose();
  d_inputDevice.reset();

  d_resourceController->dispose();
  d_resourceController.reset();

  d_renderDevice->dispose();
  d_renderDevice.reset();
}
