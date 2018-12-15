#pragma once

#include "Object.h"
#include "ObjectProperty.h"


class Creature : public Object
{
public:

  Creature();

  virtual bool isCreature() const { return true; }

private:

  ObjectProperty<int> d_health;
};
