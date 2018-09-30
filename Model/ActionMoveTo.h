#pragma once

#include "IAction.h"

#include <Sdk/Vector.h>


class ActionMoveTo : public IAction
{
public:
  ActionMoveTo(Vector2 i_goal, float i_tolerance = 0.5f)
    : d_goal(std::move(i_goal))
    , d_tolerance(i_tolerance)
    , d_toleranceSq(i_tolerance * i_tolerance)
  {
  }

  const Vector2& getGoal() const { return d_goal; }
  float getTolerance() const { return d_tolerance; }
  float getToleranceSq() const { return d_toleranceSq; }

private:
  Vector2 d_goal;
  float d_tolerance;
  float d_toleranceSq;
};
