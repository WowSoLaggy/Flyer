#include "stdafx.h"
#include "WorldController.h"

#include "ObjectController.h"

#include <Model/World.h>


void WorldController::updateWorld(World& io_world, double i_dt)
{
  for (auto& object : io_world.getObjects())
    ObjectController::updateObject(object, i_dt, io_world);
}
