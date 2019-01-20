#include "stdafx.h"
#include "Object.h"

#include "ActionIdle.h"


Object::Object()
  : d_movementDirection{ 0, 0, 0 }
  , d_speed{ 0, 0, 0 }
{
  setCurrentAction(std::make_shared<ActionIdle>());
  d_collisionShape.setRadius(0.5);
}


void Object::setCurrentAction(std::shared_ptr<IAction> i_action)
{
  if (!i_action)
    return;
  d_currentAction = i_action;
}
