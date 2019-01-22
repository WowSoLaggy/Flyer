#include "stdafx.h"
#include "IWorldController.h"

#include "WorldController.h"


std::shared_ptr<IWorldController> IWorldController::create(World& io_world)
{
  return std::make_shared<WorldController>(io_world);
}
