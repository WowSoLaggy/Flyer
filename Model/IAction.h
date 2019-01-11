#pragma once


enum class ActionType : int
{
  Idle = 0,
  MoveTo,
};


class IAction
{
public:
  virtual ~IAction() = default;

  virtual ActionType getActionType() const = 0;
};
