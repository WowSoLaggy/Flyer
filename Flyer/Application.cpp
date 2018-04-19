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
  d_drawer.init();

  d_renderDevice.initialize();
  d_drawer.load(d_renderDevice);

  d_map = std::make_unique<Map>(MapCreator::createMap());
  d_map->load(d_renderDevice);
}

void Application::mainloop()
{
  bool runGame = true;
  d_timer.Start();
  while (runGame)
  {
    if (winPeekExit())
      break;

    Updater::update(d_timer.Restart(), *d_map);
    d_drawer.draw(d_renderDevice, *d_map);

    Sleep(10);
  } // while (runGame)
}

void Application::dispose()
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
