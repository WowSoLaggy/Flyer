#pragma once

#include "Object.h"
#include "ObjectProperty.h"


class Creature : public Object
{
public:

  virtual bool isCreature() const { return true; }

  ObjectProperty<int>& getPropHealth() { return d_health; }
  const ObjectProperty<int>& getPropHealth() const { return d_health; }

  ObjectProperty<double>& getPropAttackCooldown() { return d_attackCooldown; }
  const ObjectProperty<double>& getPropAttackCooldown() const { return d_attackCooldown; }

  ObjectProperty<int>& getPropDamage() { return d_damage; }
  const ObjectProperty<int>& getPropDamage() const { return d_damage; }

private:

  ObjectProperty<int> d_health;
  ObjectProperty<double> d_attackCooldown;
  ObjectProperty<int> d_damage;
};
