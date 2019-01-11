#pragma once

#include "IAction.h"
#include "ModelFwd.h"


class ActionAttack : public IAction
{
public:
  ActionAttack(CreaturePtr i_target)
    : d_target(i_target)
  {
  }

  virtual ActionType getActionType() const override { return ActionType::Attack; }

  CreaturePtr getTarget() const { return d_target; }

private:
  CreaturePtr d_target;
};
