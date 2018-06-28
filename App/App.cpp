#include "stdafx.h"
#include "App.h"

#include <Sdk/Timer.h>


void App::run()
{
  initialize();
  mainloop();
  dispose();
}


void App::initialize()
{
}

void App::mainloop()
{
  Timer timer;
  timer.start();
  double dt = 0;

  while (true)
  {
    if (winPeekExit())
      break;

    dt = timer.restart();
  }
}

void App::dispose()
{
}


bool App::winPeekExit()
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
