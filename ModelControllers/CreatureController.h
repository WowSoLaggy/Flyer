#pragma once

#include "ModelControllersFwd.h"

#include <Model/ModelFwd.h>


class CreatureController
{
public:
  CreatureController() = delete;

  static void updateCreature(CreaturePtr io_creature, double i_dt, WorldController& io_worldController);

private:
  static void updateCreatureState(CreaturePtr io_creature, double i_dt);
  static void selectCreatureAction(CreaturePtr io_creature, WorldController& io_worldController);
  static void performCreatureAction(CreaturePtr io_creature, WorldController& io_worldController);
};
