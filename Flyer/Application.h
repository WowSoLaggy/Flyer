#pragma once

#include "Map.h"
#include "Timer.h"
#include "RenderDevice.h"


class Application
{
public:

  void run();

private:

  std::unique_ptr<Map> d_map;
  Timer d_timer;

  RenderDevice d_renderDevice;

  void initialize();
  void mainloop();
  void dispose();

  bool winPeekExit();

};
