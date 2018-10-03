#pragma once

#include <Model/ModelFwd.h>


class WorldController
{
public:

  static std::shared_ptr<World> createNewWorld();

  static void updateWorld(World& io_world, double i_dt);

private:

  WorldController() = default;

};
