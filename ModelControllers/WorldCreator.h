#pragma once

#include <Model/ModelFwd.h>


class WorldCreator
{
public:

  static std::shared_ptr<World> createNewWorld();

private:
  WorldCreator() = default;
};
