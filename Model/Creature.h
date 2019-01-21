#pragma once

#include "Object.h"

#include <Sdk/Property.h>


class Creature : public Object
{
public:

  Creature();

  virtual bool isCreature() const { return true; }
  virtual bool isMovable() const override { return true; }
  virtual float getAcceleration() const override { return 10.0f; }
  virtual float getMaxSpeed() const override { return 2.0f; }

  bool isAiControlled() const { return d_aiControlled; }
  void setAiControlled(bool i_aiControlled) { d_aiControlled = i_aiControlled; }

  auto& getPropHealth() { return d_health; }
  const auto& getPropHealth() const { return d_health; }

  auto& getPropAttackCooldown() { return d_attackCooldown; }
  const auto& getPropAttackCooldown() const { return d_attackCooldown; }

  auto& getPropDamage() { return d_damage; }
  const auto& getPropDamage() const { return d_damage; }

private:

  bool d_aiControlled;

  Property<int> d_health;
  Property<double> d_attackCooldown;
  Property<int> d_damage;
};
