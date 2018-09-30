#include "stdafx.h"
#include "App.h"

#include <Engine/IEngine.h>
#include <InputApi/InputMessage.h>


bool App::handleMessages()
{
  MSG msg;
  while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
  {
    switch (msg.message)
    {
    case WM_QUIT:
      return false;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYUP:
      d_engine->processMessage({ msg.message, msg.wParam, msg.lParam });
      break;
    }

    DispatchMessage(&msg);
  }

  return true;
}
