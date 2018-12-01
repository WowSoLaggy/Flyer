#include "stdafx.h"
#include "Object.h"

#include "ActionIdle.h"


ObjectId Object::s_nextId = 0;


Object::Object()
  : d_id(s_nextId++)
  , d_modelName("")
  , d_position{ 0, 0, 0 }
  , d_rotation{ 0, 0, 0 }
  , d_visible(true)
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

