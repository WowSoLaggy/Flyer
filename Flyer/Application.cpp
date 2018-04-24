#include "stdafx.h"
#include "Application.h"

#include "MapCreator.h"
#include "Updater.h"
#include "Drawer.h"


void Application::run()
{
  initialize();
  mainloop();
  dispose();
}

void Application::initialize()
{
  d_resourceController.indexResources();
  d_drawer.init();
}

void Application::mainloop()
{
  double dt;
  d_timer.Start();
  
  bool runGame = true;
  while (runGame)
  {
    if (winPeekExit())
      break;

    dt = d_timer.Restart();

    if (!d_renderDevice.isInitialized())
    {
      createRenderDevice();
      continue;
    }

    Updater::update(dt, *d_map);
    d_drawer.draw(d_renderDevice, *d_map);

    Sleep(10);
  } // while (runGame)
}

void Application::dispose()
{
  if (d_renderDevice.isInitialized())
    disposeRenderDevice();
  d_resourceController.clearIndices();
}


void Application::createRenderDevice()
{
  d_renderDevice.initialize();
  d_drawer.load(d_renderDevice);

  d_map = std::make_unique<Map>(MapCreator::createMap());
  d_map->load(d_renderDevice);
}

void Application::disposeRenderDevice()
{
  d_map->unload();
  d_map.reset();

  d_drawer.unload();
  d_renderDevice.dispose();
}


bool Application::winPeekExit()
{
  MSG msg;
  UINT res = 0;

  if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    res = msg.message;
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (res == WM_QUIT);
}
