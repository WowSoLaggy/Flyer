#pragma once

#include <Model/ModelFwd.h>


class WorldCreator
{
public:

  static std::shared_ptr<World> createNewWorld();
  static CreaturePtr createCreature();

private:
  WorldCreator() = default;

  static void createObjects(ObjectPtrs& o_objects);
};
