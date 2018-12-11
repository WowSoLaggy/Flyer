#pragma once

#include "ModelControllersFwd.h"


class WorldCreator
{
public:

  static std::shared_ptr<WorldWrapper> createNewWorld();

private:
  WorldCreator() = default;
};
