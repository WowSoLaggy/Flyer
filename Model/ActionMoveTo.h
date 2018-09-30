#pragma once

#include "IAction.h"

#include <Sdk/Vector.h>


class ActionMoveTo: public IAction
{
public:
  ActionMoveTo(Vector2 i_goal)
    : d_goal(std::move(i_goal))
  {
  }

  const Vector2& getGoal() const { return d_goal; }

private:
  Vector2 d_goal;
};
