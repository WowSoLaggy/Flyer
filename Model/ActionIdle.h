#pragma once

#include "IAction.h"


class ActionIdle : public IAction
{
public:

  virtual ActionType getActionType() const override { return ActionType::Idle; }

};
