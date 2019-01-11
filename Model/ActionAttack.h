#pragma once

#include "IAction.h"
#include "ModelFwd.h"


class ActionAttack : public IAction
{
public:
  ActionAttack(ObjectPtr i_target)
    : d_target(i_target)
  {
  }

  virtual ActionType getActionType() const override { return ActionType::Attack; }

  ObjectPtr getTarget() const { return d_target; }

private:
  ObjectPtr d_target;
};
