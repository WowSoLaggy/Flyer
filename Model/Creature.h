#pragma once

#include "Object.h"
#include "ObjectProperty.h"


class Creature : public Object
{
public:

  virtual bool isCreature() const { return true; }

  ObjectProperty<int>& getPropHealth() { return d_health; }
  const ObjectProperty<int>& getPropHealth() const { return d_health; }

private:

  ObjectProperty<int> d_health;
};
