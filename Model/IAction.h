#pragma once


enum class ActionType : int
{
  Idle = 0,
  Hold,
  MoveTo,
};


class IAction
{
public:
  virtual ~IAction() = default;

  virtual ActionType getActionType() const = 0;
};
