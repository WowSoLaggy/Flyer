#pragma once

#include <Model/ModelFwd.h>
#include <Sdk/IEvent.h>


class ObjectAddedEvent : public IEvent
{
public:

  ObjectAddedEvent(ObjectPtr i_object)
    : d_object(i_object)
  {
  }

  ObjectPtr getObject() const { return d_object; }

private:

  ObjectPtr d_object;
};


class ObjectDeletedEvent : public IEvent
{
public:

  ObjectDeletedEvent(ObjectPtr i_object)
    : d_object(i_object)
  {
  }

  ObjectPtr getObject() const { return d_object; }

private:

  ObjectPtr d_object;
};


class ObjectChangedActionEvent : public IEvent
{
public:

  ObjectChangedActionEvent(ObjectPtr i_object, IActionPtr i_previousAction)
    : d_object(i_object)
    , d_previousAction(i_previousAction)
  {
  }

  ObjectPtr getObject() const { return d_object; }
  IActionPtr getPreviousAction() const { return d_previousAction; }

private:

  ObjectPtr d_object;
  IActionPtr d_previousAction;

};
