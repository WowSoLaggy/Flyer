#pragma once

#include "Object.h"
#include "ObjectProperty.h"


class Creature : public Object
{
public:

  Creature();

  virtual bool isCreature() const { return true; }
  virtual bool isMovable() const override { return true; }

  bool isAiControlled() const { return d_aiControlled; }
  void setAiControlled(bool i_aiControlled) { d_aiControlled = i_aiControlled; }

  ObjectProperty<int>& getPropHealth() { return d_health; }
  const ObjectProperty<int>& getPropHealth() const { return d_health; }

  ObjectProperty<double>& getPropAttackCooldown() { return d_attackCooldown; }
  const ObjectProperty<double>& getPropAttackCooldown() const { return d_attackCooldown; }

  ObjectProperty<int>& getPropDamage() { return d_damage; }
  const ObjectProperty<int>& getPropDamage() const { return d_damage; }

private:

  bool d_aiControlled;

  ObjectProperty<int> d_health;
  ObjectProperty<double> d_attackCooldown;
  ObjectProperty<int> d_damage;
};
