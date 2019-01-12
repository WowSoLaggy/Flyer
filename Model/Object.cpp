#include "stdafx.h"
#include "Object.h"

#include "ActionIdle.h"


ObjectId Object::s_nextId = 0;


Object::Object()
  : d_id(s_nextId++)
  , d_modelName("")
  , d_movementDirection{ 0, 0, 0 }
  , d_position{ 0, 0, 0 }
  , d_speed{ 0, 0, 0 }
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


///
/// IRealObject
///


bool Object::isMovable() const { return false; }
float Object::getAcceleration() const { return 10.0f; }
float Object::getMaxSpeed() const { return 2.0f; }
Vector3 Object::getMovementDirection() const { return d_movementDirection; }

Vector3 Object::getPosition() const { return d_position; }
void Object::setPosition(Vector3 i_position) { d_position = std::move(i_position); }

Vector3 Object::getSpeed() const { return d_speed; }
void Object::setSpeed(Vector3 i_speed) { d_speed = std::move(i_speed); }

///

void Object::setMovementDirection(Vector3 i_movementDirection) { d_movementDirection = std::move(i_movementDirection); }
void Object::resetMovementDirection() { d_movementDirection = Vector3::zero(); }
