#include "stdafx.h"
#include "ObjectConverters.h"

#include "Creature.h"
#include "Object.h"


CreaturePtr castObjectToCreature(ObjectPtr i_objectPtr)
{
  return std::dynamic_pointer_cast<Creature>(i_objectPtr);
}
