#include "stdafx.h"
#include "Engine.h"

#include <RenderApi/IRenderDevice.h>
#include <Sdk/Timer.h>


void Engine::run(ControlCallback i_controlCallback, UpdateCallback i_updateCallback)
{
  Timer timer;
  timer.start();
  double dt = 0;

  while (i_controlCallback() == ControlSignal::Run)
  {
    dt = timer.restart();

    i_updateCallback(dt);

    if (d_pRenderDevice->isInitialized())
    {
      d_pRenderDevice->beginScene();
      // TODO: delete sleep
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      d_pRenderDevice->endScene();
    }

    // TODO: delete sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}


void Engine::initialize()
{
  d_pRenderDevice = IRenderDevice::create();
}

void Engine::dispose()
{
  d_pRenderDevice->dispose();
  d_pRenderDevice.reset();
}
