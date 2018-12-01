#include "stdafx.h"
#include "Object.h"

#include "ActionIdle.h"


Object::Object()
  : d_modelName("")
  , d_position{ 0, 0, 0 }
  , d_rotation{ 0, 0, 0 }
{
  setCurrentAction(std::make_shared<ActionIdle>());
}


void Object::setCurrentAction(std::shared_ptr<IAction> i_action)
{
  if (!i_action)
    return;
  d_currentAction = i_action;
}

IAction& Object::getCurrentAction()
{
  return *d_currentAction;
}

const IAction& Object::getCurrentAction() const
{
  return *d_currentAction;
}

