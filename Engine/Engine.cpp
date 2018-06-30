#include "stdafx.h"
#include "Engine.h"

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

    if (d_renderDevice.isCreated())
    {
      d_renderDevice.beginScene();
      // TODO: delete sleep
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      d_renderDevice.endScene();
    }

    // TODO: delete sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
