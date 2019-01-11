#pragma once

#include "IAction.h"
#include "ModelFwd.h"
#include "Object.h"

#include <Sdk/Vector.h>


class ActionMoveTo : public IAction
{
public:
  ActionMoveTo(ObjectPtr i_goalObject, float i_tolerance = 0.5f)
    : d_goalObject(i_goalObject)
    , d_tolerance(i_tolerance)
    , d_toleranceSq(i_tolerance * i_tolerance)
  {
  }

  ActionMoveTo(Vector2 i_goal, float i_tolerance = 0.5f)
    : d_goal(std::move(i_goal))
    , d_tolerance(i_tolerance)
    , d_toleranceSq(i_tolerance * i_tolerance)
  {
  }

  virtual ActionType getActionType() const override { return ActionType::MoveTo; }

  Vector2 getGoal() const { return d_goalObject ? xyz2xz(d_goalObject->getPosition()) : d_goal; }
  float getTolerance() const { return d_tolerance; }
  float getToleranceSq() const { return d_toleranceSq; }

private:
  ObjectPtr d_goalObject;
  Vector2 d_goal;
  float d_tolerance;
  float d_toleranceSq;
};
