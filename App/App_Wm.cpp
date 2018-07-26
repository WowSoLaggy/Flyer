#include "stdafx.h"
#include "App.h"


bool App::handleMessages()
{
  MSG msg;
  while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
  {
    switch (msg.message)
    {
    case WM_QUIT:
      return false;
    }

    DispatchMessage(&msg);
  }

  return true;
}
