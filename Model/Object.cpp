#include "stdafx.h"
#include "Object.h"


void Object::setCurrentAction(std::shared_ptr<IAction> i_action)
{
  d_currentAction = i_action;
}

void Object::resetCurrentAction()
{
  d_currentAction.reset();
}

std::shared_ptr<IAction> Object::getCurrentAction() const
{
  return d_currentAction;
}
