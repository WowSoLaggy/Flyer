#pragma once

#include "IAction.h"


class ActionHold : public IAction
{
public:
  ActionHold(double i_holdTime)
    : d_holdTime(i_holdTime)
  {
  }

  virtual ActionType getActionType() const override { return ActionType::Hold; }

  bool hold(double i_dt)
  {
    d_holdTime -= i_dt;
    return d_holdTime >= 0;
  }

private:
  double d_holdTime;
};
