#pragma once


enum class ActionType : int
{
  Idle = 0,
  MoveTo,
  Attack,
};


class IAction
{
public:
  virtual ~IAction() = default;

  virtual ActionType getActionType() const = 0;
};
