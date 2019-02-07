#include "stdafx.h"
#include "Object.h"

#include "ActionIdle.h"


Object::Object()
  : d_movable(false)
  , d_acceleration(0.0f)
  , d_maxSpeed(0.0f)
  , d_movementDirection{ Vector3::zero() }
{
  setCurrentAction(std::make_shared<ActionIdle>());
}


void Object::setCurrentAction(std::shared_ptr<IAction> i_action)
{
  d_currentAction = i_action ? i_action : std::make_shared<ActionIdle>();
}
