#pragma once

#include <Model/ModelFwd.h>


class WorldController
{
public:

  std::shared_ptr<World> createNewWorld();

private:

  WorldController() = default;

};
