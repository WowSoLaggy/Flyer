#pragma once

#include "ModelControllersFwd.h"

#include <Model/ModelFwd.h>


class CreatureController
{
public:
  CreatureController() = delete;

  static void updateObject(CreaturePtr io_creature, double i_dt, WorldController& io_worldController);
};
