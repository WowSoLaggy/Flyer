#pragma once

#include <Model/ModelFwd.h>


class WorldController
{
public:

  static void updateWorld(World& io_world, double i_dt);

private:
  WorldController() = default;
};
