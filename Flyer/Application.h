#pragma once

#include "Drawer.h"
#include "Map.h"
#include "RenderDevice.h"
#include "ResourceController.h"
#include "Timer.h"


class Application
{
public:

  void run();

private:

  std::unique_ptr<Map> d_map;
  Timer d_timer;
  Drawer d_drawer;
  RenderDevice d_renderDevice;
  ResourceController d_resourceController;

  void initialize();
  void mainloop();
  void dispose();

  bool winPeekExit();

};
