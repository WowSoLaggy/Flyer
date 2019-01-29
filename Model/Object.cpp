#include "stdafx.h"
#include "Object.h"

#include "ActionIdle.h"


Object::Object()
  : d_movementDirection{ Vector3::zero() }
{
  setCurrentAction(std::make_shared<ActionIdle>());
}


void Object::setCurrentAction(std::shared_ptr<IAction> i_action)
{
  if (!i_action)
    return;
  d_currentAction = i_action;
}
