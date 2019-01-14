#pragma once

#include <Model/ModelFwd.h>


class WorldCreator
{
public:

  static std::shared_ptr<World> createNewWorld();
  static CreaturePtr createCreature();

private:
  WorldCreator() = default;

  static void createArenaObjects(ObjectPtrs& o_objects);

  static ObjectPtr createObject(ObjectPtrs& o_objects);
  static CreaturePtr createCreature(ObjectPtrs& o_objects);
};
