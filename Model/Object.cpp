#include "stdafx.h"
#include "Object.h"

#include "ActionIdle.h"


Object::Object()
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

