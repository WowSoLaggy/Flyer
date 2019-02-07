#pragma once

#include "ControlledBy.h"
#include "Object.h"

#include <Sdk/Property.h>


class Creature : public Object
{
public:

  Creature();

  virtual bool isCreature() const { return true; }

  ControlledBy getControlledBy() const { return d_controlledBy; }
  void setControlledBy(ControlledBy i_controlledBy) { d_controlledBy = i_controlledBy; }

  auto& getPropHealth() { return d_health; }
  const auto& getPropHealth() const { return d_health; }

  auto& getPropAttackCooldown() { return d_attackCooldown; }
  const auto& getPropAttackCooldown() const { return d_attackCooldown; }

  auto& getPropDamage() { return d_damage; }
  const auto& getPropDamage() const { return d_damage; }

private:

  ControlledBy d_controlledBy;

  Property<int> d_health;
  Property<double> d_attackCooldown;
  Property<int> d_damage;
};
