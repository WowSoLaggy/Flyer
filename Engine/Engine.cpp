#include "stdafx.h"
#include "Engine.h"

#include <RenderApi/IRenderDevice.h>
#include <Sdk/Timer.h>


void Engine::run(
  ControlCallback i_controlCallback,
  UpdateCallback i_updateCallback,
  RenderCallback i_renderCallback)
{
  Timer timer;
  timer.start();
  double dt = 0;

  while (i_controlCallback() == ControlSignal::Run)
  {
    dt = timer.restart();

    i_updateCallback(dt);

    if (d_renderDevice->isInitialized())
    {
      d_renderDevice->beginScene();
      // TODO: delete sleep
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      d_renderDevice->endScene();
    }

    // TODO: delete sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}


void Engine::initialize()
{
  d_renderDevice = IRenderDevice::create();
}

void Engine::dispose()
{
  d_renderDevice->dispose();
  d_renderDevice.reset();
}
