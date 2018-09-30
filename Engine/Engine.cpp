#include "stdafx.h"
#include "Engine.h"

#include <InputApi/IInputDevice.h>
#include <RenderApi/IRenderDevice.h>
#include <RenderApi/IResourceController.h>
#include <Sdk/Timer.h>


void Engine::run(
  ControlCallback i_controlCallback,
  UpdateCallback i_updateCallback,
  RenderCallback i_renderCallback,
  InputCallback i_inputCallback)
{
  Timer timer;
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

      i_renderCallback();

      // TODO: delete sleep
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      d_renderDevice->endScene();
    }

    // TODO: delete sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}


void Engine::initialize(const std::string& i_resourceFolder)
{
  d_renderDevice = IRenderDevice::create();

  d_resourceController = IResourceController::create();
  d_resourceController->initialize(i_resourceFolder);

  d_inputDevice = IInputDevice::create();
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
